#include "ppl/nn/engines/cuda/optimizer/ops/onnx/concat_op.h"

#include "ppl/nn/common/logger.h"
#include "ppl/nn/engines/cuda/kernels/onnx/concat_kernel.h"
#include "ppl/nn/oputils/onnx/reshape_concat.h"

using namespace std;
using namespace ppl::common;
using namespace ppl::nn::common;

namespace ppl { namespace nn { namespace cuda {

RetCode ConcatOp::Init(const OptKernelOptions& options) {
    auto status = GenericLoadParam<ConcatParam>(options, &param_.param);
    if (status != RC_SUCCESS) {
        LOG(ERROR) << "load param failed: " << GetRetCodeStr(status);
        return status;
    }

    infer_type_func_ = [this](InputOutputInfo* info, datatype_t type) -> RetCode {
        return type != DATAFORMAT_UNKNOWN ? InferDefaultType(info, type) : InferHighestType(info);
    };

    infer_dims_func_ = [this](InputOutputInfo* info) -> RetCode {
        return oputils::ReshapeConcat(info, &param_);
    };

    infer_unsafe_dims_func_ = [this](InputOutputInfo* info, std::set<uint32_t>* illegal_inputs) -> RetCode {
        auto in_shape0 = &info->GetInput<TensorImpl>(0)->GetShape();
        for (uint32_t i = 0; i < info->GetInputCount(); ++i) {
            if (illegal_inputs->find(i) != illegal_inputs->end()) {
                in_shape0 = &info->GetInput<TensorImpl>(i)->GetShape();
                break;
            }
        }

        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            auto out_shape = &info->GetOutput<TensorImpl>(i)->GetShape();
            out_shape->Reshape(in_shape0->GetDims(), in_shape0->GetRealDimCount());
        }
        return ppl::common::RC_SUCCESS;
    };

    return RC_SUCCESS;
}

RetCode ConcatOp::Finalize(const OptKernelOptions& options) {
    auto status = SetCommonParam(options);
    if (status != RC_SUCCESS) {
        LOG(ERROR) << "load common param failed: " << GetRetCodeStr(status);
        return status;
    }

    return RC_SUCCESS;
}

KernelImpl* ConcatOp::CreateKernelImpl() const {
    return CreateKernelImplWithParam<ConcatKernel>(&param_);
}

}}} // namespace ppl::nn::cuda
