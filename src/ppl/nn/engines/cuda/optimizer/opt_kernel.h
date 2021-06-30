#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_OPT_KERNEL_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_OPT_KERNEL_H_

#include "ppl/nn/runtime/opt_kernel.h"

#include <set>
#include <map>
#include <string>

#include "ppl/common/retcode.h"
#include "ppl/common/types.h"
#include "ppl/nn/common/logger.h"
#include "ppl/nn/ir/graph.h"
#include "ppl/nn/engines/cuda/engine.h"
#include "ppl/nn/engines/cuda/cuda_device.h"
#include "ppl/nn/engines/cuda/cuda_common_param.h"
#include "ppl/nn/runtime/tensor_impl.h"
#include "ppl/nn/runtime/runtime_graph_info.h"
#include "ppl/nn/runtime/runtime_partition_info.h"

namespace ppl { namespace nn { namespace utils {
struct SharedResource;
}}} // namespace ppl::nn::utils

namespace ppl { namespace nn { namespace cuda {

struct OptKernelOptions {
    OptKernelOptions(ir::Graph* graph, RuntimePartitionInfo* info, utils::SharedResource* resource, CudaArgs* args,
                     CudaDevice* device, std::map<edgeid_t, std::unique_ptr<TensorImpl>>* tensors)
        : graph(graph), info(info), resource(resource), args(args), device(device), tensors(tensors) {}

    OptKernelOptions(ir::Graph* graph, RuntimePartitionInfo* info, utils::SharedResource* resource,
                     std::map<edgeid_t, std::unique_ptr<TensorImpl>>* tensors)
        : graph(graph), info(info), resource(resource), tensors(tensors) {}

    OptKernelOptions(ir::Graph* graph, utils::SharedResource* resource) : graph(graph), resource(resource) {}

    ir::Graph* graph;
    RuntimePartitionInfo* info;
    utils::SharedResource* resource;
    CudaArgs* args;
    CudaDevice* device;
    std::map<edgeid_t, std::unique_ptr<TensorImpl>>* tensors;
    void* param;
};

class CudaOptKernel : public OptKernel {
public:
    CudaOptKernel(const ir::Node* node) : OptKernel(node) {}
    virtual ~CudaOptKernel() {}

    virtual ppl::common::RetCode Init(const OptKernelOptions& options) = 0;
    virtual ppl::common::RetCode Finalize(const OptKernelOptions& options) = 0;
    virtual void* GetParam() {
        return nullptr;
    }
    virtual void CopyParam(void*& param) {
        param = nullptr;
    }
    virtual bool CompareParam(CudaOptKernel* other) {
        return false;
    }

    CudaCommonParam* GetCommparam() {
        return &common_param_;
    }

    ppl::common::RetCode InferType(InputOutputInfo* info, ppl::common::datatype_t type) const {
        return infer_type_func_(info, type);
    }

    ppl::common::RetCode InferDims(InputOutputInfo* info) const {
        return infer_dims_func_(info);
    }

    ppl::common::RetCode InferUnsafeDims(InputOutputInfo* info, std::set<uint32_t>* illegal_inputs) const {
        return infer_unsafe_dims_func_(info, illegal_inputs);
    }

protected:
    ppl::common::RetCode SetCommonParam(const OptKernelOptions&);

    template <typename T>
    ppl::common::RetCode GenericLoadParam(const OptKernelOptions& options, T* param) {
        auto node = GetNode();
        auto graph_data = options.graph->data.get();
        auto param_ref = graph_data->attrs.find(node->GetId());
        if (param_ref == graph_data->attrs.end()) {
            return ppl::common::RC_NOT_FOUND;
        }
        *param = *((const T*)param_ref->second.get());
        return ppl::common::RC_SUCCESS;
    }

    template <typename KernelType, typename ParamType>
    KernelType* CreateKernelImplWithParam(const ParamType* param) const {
        auto kernel = new KernelType(GetNode());
        auto status = kernel->Init();
        if (status != ppl::common::RC_SUCCESS) {
            delete kernel;
            return nullptr;
        }
        kernel->SetParam(param);
        kernel->SetCommonParam(&common_param_);
        kernel->SetReshapeFunc([this](InputOutputInfo* info) -> ppl::common::RetCode {
            auto status = infer_dims_func_(info);
            GenericInferTypeAndFormat(info);
            return status;
        });
        return kernel;
    }

    template <typename KernelType>
    KernelType* CreateKernelImplWithoutParam() const {
        auto kernel = new KernelType(GetNode());
        auto status = kernel->Init();
        if (status != ppl::common::RC_SUCCESS) {
            delete kernel;
            return nullptr;
        }
        kernel->SetCommonParam(&common_param_);
        kernel->SetReshapeFunc([this](InputOutputInfo* info) -> ppl::common::RetCode {
            auto status = infer_dims_func_(info);
            GenericInferTypeAndFormat(info);
            return status;
        });
        return kernel;
    }

    static ppl::common::RetCode GenericInferDims(InputOutputInfo* info) {
        auto& in_shape0 = info->GetInput<TensorImpl>(0)->GetShape();
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            info->GetOutput<TensorImpl>(i)->GetShape().Reshape(in_shape0.GetDims(), in_shape0.GetRealDimCount());
        }
        return ppl::common::RC_SUCCESS;
    }

    static ppl::common::RetCode GenericUnsafeInferDims(InputOutputInfo* info, std::set<uint32_t>* mask) {
        auto& in_shape0 = info->GetInput<TensorImpl>(0)->GetShape();
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            info->GetOutput<TensorImpl>(i)->GetShape().Reshape(in_shape0.GetDims(), in_shape0.GetRealDimCount());
        }
        return ppl::common::RC_SUCCESS;
    }

    static ppl::common::RetCode InferDefaultType(InputOutputInfo* info, ppl::common::datatype_t type) {
        for (uint32_t i = 0; i < info->GetInputCount(); ++i) {
            auto in_shape = &info->GetInput<TensorImpl>(i)->GetShape();
            in_shape->SetDataType(type);
        }
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            auto out_shape = &info->GetOutput<TensorImpl>(i)->GetShape();
            out_shape->SetDataType(type);
        }
        return ppl::common::RC_SUCCESS;
    }

    static ppl::common::RetCode InferInheritedType(InputOutputInfo* info) {
        auto in_shape = &info->GetInput<TensorImpl>(0)->GetShape();
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            auto out_shape = &info->GetOutput<TensorImpl>(i)->GetShape();
            out_shape->SetDataType(in_shape->GetDataType());
        }
        return ppl::common::RC_SUCCESS;
    }

    static ppl::common::RetCode InferHighestType(InputOutputInfo* info, uint64_t mask = 0) {
        ppl::common::datatype_t highest = ppl::common::DATATYPE_UNKNOWN;
        for (uint32_t i = 0; i < info->GetInputCount(); ++i) {
            if (i < 64 && mask & (1 << i)) {
                continue;
            }
            auto in_shape = &info->GetInput<TensorImpl>(i)->GetShape();
            if (in_shape->GetDataType() > highest) {
                highest = in_shape->GetDataType();
            }
        }

        if (highest == ppl::common::DATATYPE_UNKNOWN) {
            LOG(DEBUG) << "all inputs is constants or some inputs have unknown input type.";
        }

        for (uint32_t i = 0; i < info->GetInputCount(); ++i) {
            auto in_shape = &info->GetInput<TensorImpl>(i)->GetShape();
            in_shape->SetDataType(highest);
        }
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            auto out_shape = &info->GetOutput<TensorImpl>(i)->GetShape();
            out_shape->SetDataType(highest);
        }

        return ppl::common::RC_SUCCESS;
    }

private:
    void GenericInferTypeAndFormat(InputOutputInfo* info) const {
        auto pre_shape = &info->GetInput<TensorImpl>(0)->GetShape();
        for (uint32_t i = 0; i < info->GetOutputCount(); ++i) {
            auto tensor_shape = &info->GetOutput<TensorImpl>(i)->GetShape();
            auto data_type = common_param_.output_tensor_info.at(i).data_type;
            auto data_foramt = common_param_.output_tensor_info.at(i).data_format;
            tensor_shape->SetDataType(data_type == ppl::common::DATATYPE_UNKNOWN ? pre_shape->GetDataType()
                                                                                 : data_type);
            tensor_shape->SetDataFormat(data_type == ppl::common::DATAFORMAT_UNKNOWN ? pre_shape->GetDataFormat()
                                                                                     : data_foramt);
        }
    }

protected:
    std::function<ppl::common::RetCode(InputOutputInfo*)> infer_dims_func_;
    std::function<ppl::common::RetCode(InputOutputInfo*, std::set<uint32_t>*)> infer_unsafe_dims_func_ =
        GenericUnsafeInferDims;
    std::function<ppl::common::RetCode(InputOutputInfo*, ppl::common::datatype_t)> infer_type_func_;

private:
    CudaCommonParam common_param_;
};

}}} // namespace ppl::nn::cuda

#endif
