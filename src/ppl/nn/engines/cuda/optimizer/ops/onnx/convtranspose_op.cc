#include "ppl/nn/engines/cuda/optimizer/ops/onnx/convtranspose_op.h"

#include "ppl/nn/common/logger.h"
#include "ppl/nn/engines/cuda/kernels/onnx/convtranspose_kernel.h"
#include "ppl/nn/oputils/onnx/reshape_convtranspose.h"

using namespace std;
using namespace ppl::common;
using namespace ppl::nn::common;

namespace ppl { namespace nn { namespace cuda {

RetCode ConvTransposeOp::Init(const OptKernelOptions& options) {
    auto status = GenericLoadParam<ConvTransposeParam>(options, &param_);
    if (status != RC_SUCCESS) {
        LOG(ERROR) << "load param failed: " << GetRetCodeStr(status);
        return status;
    }

    infer_type_func_ = [this](InputOutputInfo* info, datatype_t type) -> RetCode {
        if (type == ppl::common::DATATYPE_UNKNOWN) {
            type = ppl::common::DATATYPE_FLOAT16;
        }
        return InferDefaultType(info, type);
    };

    infer_dims_func_ = [this](InputOutputInfo* info) -> RetCode {
        return oputils::ReshapeConvTranspose(info, &param_);
    };

    return RC_SUCCESS;
}

RetCode ConvTransposeOp::Finalize(const OptKernelOptions& options) {
    auto status = SetCommonParam(options);
    if (status != RC_SUCCESS) {
        LOG(ERROR) << "load common param failed: " << GetRetCodeStr(status);
        return status;
    }

    return RC_SUCCESS;
}

KernelImpl* ConvTransposeOp::CreateKernelImpl() const {
    return CreateKernelImplWithParam<ConvTransposeKernel>(&param_);
}

}}} // namespace ppl::nn::cuda
