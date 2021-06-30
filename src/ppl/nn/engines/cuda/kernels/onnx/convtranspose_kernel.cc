#include "ppl/nn/engines/cuda/kernels/onnx/convtranspose_kernel.h"

#include "cudakernel/nn/convtranspose.h"

namespace ppl { namespace nn { namespace cuda {

uint64_t ConvTransposeKernel::CalcTmpBufferSize(const KernelExecContext& ctx) const {
    auto x = ctx.GetInput<TensorImpl>(0);
    auto y = ctx.GetOutput<TensorImpl>(0);

    return PPLConvTransposeGetBufSizeCuda(&x->GetShape(), &y->GetShape(), param_);
}

ppl::common::RetCode ConvTransposeKernel::DoExecute(KernelExecContext* ctx) {
    BufferDesc tmp_buffer_desc;
    auto tmp_buffer_bytes = CalcTmpBufferSize(*ctx);
    auto status = GetCudaDevice()->AllocTmpBuffer(tmp_buffer_bytes, &tmp_buffer_desc);
    if (status != ppl::common::RC_SUCCESS) {
        LOG(ERROR) << "alloc tmp buffer size[" << tmp_buffer_bytes << "] for kernel[" << GetName()
                   << "] failed: " << ppl::common::GetRetCodeStr(status);
        return status;
    }
    BufferDescGuard __tmp_buffer_guard(&tmp_buffer_desc, [this](BufferDesc* buffer) -> void {
        GetCudaDevice()->FreeTmpBuffer(buffer);
    });
    auto tmp_buffer = tmp_buffer_desc.addr;

    TensorImpl* X = ctx->GetInput<TensorImpl>(0);
    TensorImpl* W = ctx->GetInput<TensorImpl>(1);
    TensorImpl* B = nullptr;
    TensorImpl* Y = ctx->GetOutput<TensorImpl>(0);
    const float* b_data = nullptr;

    if (ctx->GetInputCount() >= 3) {
        B = ctx->GetInput<TensorImpl>(2);
        b_data = B->GetBufferPtr<float>();
    }

    status = PPLCUDAConvTransposeForward(GetStream(), &X->GetShape(), X->GetBufferPtr(), W->GetBufferPtr(), b_data,
                                         param_, tmp_buffer, &Y->GetShape(), Y->GetBufferPtr());

    return status;
}

}}} // namespace ppl::nn::cuda
