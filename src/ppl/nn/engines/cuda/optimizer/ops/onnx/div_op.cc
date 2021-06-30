#include "ppl/nn/engines/cuda/optimizer/ops/onnx/div_op.h"

#include "ppl/nn/common/logger.h"
#include "ppl/nn/engines/cuda/kernels/onnx/div_kernel.h"
#include "ppl/nn/oputils/onnx/reshape_add.h"

using namespace std;
using namespace ppl::common;

namespace ppl { namespace nn { namespace cuda {

RetCode DivOp::Init(const OptKernelOptions& options) {
    auto node = GetNode();
    auto data = options.graph->data.get();
    for (uint32_t i = 0; i < 64 && i < node->GetInputCount(); ++i) {
        auto edge_id = node->GetInput(i);
        if (data->constants.find(edge_id) != data->constants.end()) {
            mask |= 1 << i;
        }
    }

    infer_type_func_ = [this](InputOutputInfo* info, datatype_t type) -> RetCode {
        return type != DATAFORMAT_UNKNOWN ? InferDefaultType(info, type) : InferHighestType(info, mask);
    };

    infer_dims_func_ = [this](InputOutputInfo* info) -> RetCode {
        return oputils::ReshapeAdd(info, nullptr);
    };

    return RC_SUCCESS;
}

RetCode DivOp::Finalize(const OptKernelOptions& options) {
    auto status = SetCommonParam(options);
    if (status != RC_SUCCESS) {
        LOG(ERROR) << "load common param failed: " << GetRetCodeStr(status);
        return status;
    }

    return RC_SUCCESS;
}

KernelImpl* DivOp::CreateKernelImpl() const {
    return CreateKernelImplWithoutParam<DivKernel>();
}

}}} // namespace ppl::nn::cuda
