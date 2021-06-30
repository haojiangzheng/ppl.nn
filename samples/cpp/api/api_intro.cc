#include "ppl/nn/models/onnx/onnx_runtime_builder_factory.h"
#include "ppl/nn/engines/x86/engine_factory.h"
#include <random>
#include <iostream>
using namespace std;
using namespace ppl::nn;
using namespace ppl::common;

static bool SetRandomInputs(Runtime* runtime) {
    for (uint32_t c = 0; c < runtime->GetInputCount(); ++c) {
        auto t = runtime->GetInputTensor(c);
        auto& shape = t->GetShape();

        auto nr_element = shape.GetBytesIncludingPadding() / sizeof(float);
        unique_ptr<float[]> buffer(new float[nr_element]);

        // fill random input data
        std::default_random_engine eng;
        std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
        for (uint32_t i = 0; i < nr_element; ++i) {
            buffer.get()[i] = dis(eng);
        }

        auto status = t->ReallocBuffer();
        if (status != RC_SUCCESS) {
            cerr << "ReallocBuffer for tensor[" << t->GetName() << "] failed: " << GetRetCodeStr(status) << endl;
            return false;
        }

        // our random data is treated as NDARRAY
        TensorShape src_desc = t->GetShape();
        src_desc.SetDataFormat(DATAFORMAT_NDARRAY);

        // input tensors may require different data format
        status = t->ConvertFromHost(buffer.get(), src_desc);
        if (status != RC_SUCCESS) {
            cerr << "set tensor[" << t->GetName() << "] content failed: " << GetRetCodeStr(status) << endl;
            return false;
        }
    }

    return true;
}

static void PrintInputOutputInfo(const Runtime* runtime) {
    cout << "----- input info -----" << endl;
    for (uint32_t i = 0; i < runtime->GetInputCount(); ++i) {
        auto tensor = runtime->GetInputTensor(i);
        cout << "input[" << i << "]:" << endl << "    name: " << tensor->GetName() << endl;

        string dims_str;
        auto& shape = tensor->GetShape();
        for (uint32_t j = 0; j < shape.GetDimCount(); ++j) {
            dims_str += " " + std::to_string(shape.GetDim(j));
        }
        cout << "    dim(s):" << dims_str << endl
             << "    DataType: " << GetDataTypeStr(shape.GetDataType()) << endl
             << "    DataFormat: " << GetDataFormatStr(shape.GetDataFormat()) << endl
             << "    BytesIncludePadding: " << shape.GetBytesIncludingPadding() << endl
             << "    BytesExcludePadding: " << shape.GetBytesExcludingPadding() << endl;
    }

    cout << "----- output info -----" << endl;
    for (uint32_t i = 0; i < runtime->GetOutputCount(); ++i) {
        auto tensor = runtime->GetOutputTensor(i);
        cout << "output[" << i << "]:" << endl << "    name: " << tensor->GetName();

        string dims_str;
        auto& shape = tensor->GetShape();
        for (uint32_t j = 0; j < shape.GetDimCount(); ++j) {
            dims_str += " " + std::to_string(shape.GetDim(j));
        }
        cout << "    dim(s):" << dims_str << endl
             << "    DataType: " << GetDataTypeStr(shape.GetDataType()) << endl
             << "    DataFormat: " << GetDataFormatStr(shape.GetDataFormat()) << endl
             << "    BytesIncludePadding: " << shape.GetBytesIncludingPadding() << endl
             << "    BytesExcludePadding: " << shape.GetBytesExcludingPadding() << endl;
    }

    cout << "----------------------" << endl;
}

int main(void) {
    const char* model_file = "tests/testdata/conv.onnx";

    auto x86_engine = X86EngineFactory::Create();

    vector<unique_ptr<Engine>> engines;
    engines.emplace_back(unique_ptr<Engine>(x86_engine));

    auto builder = unique_ptr<OnnxRuntimeBuilder>(OnnxRuntimeBuilderFactory::Create(model_file, std::move(engines)));
    if (!builder) {
        cerr << "create OnnxRuntimeBuilder failed." << endl;
        return -1;
    }

    RuntimeOptions runtime_options;
    auto runtime = unique_ptr<Runtime>(builder->CreateRuntime(runtime_options));
    if (!runtime) {
        cerr << "CreateRuntime failed." << endl;
        return -1;
    }

    if (!SetRandomInputs(runtime.get())) {
        cerr << "SetRandomInputs failed." << endl;
        return -1;
    }

    auto status = runtime->Run();
    if (status != RC_SUCCESS) {
        cerr << "Run() failed: " << GetRetCodeStr(status) << endl;
        return -1;
    }

    status = runtime->Sync();
    if (status != RC_SUCCESS) {
        cerr << "Sync() failed: " << GetRetCodeStr(status) << endl;
    }

    PrintInputOutputInfo(runtime.get());

    return 0;
}
