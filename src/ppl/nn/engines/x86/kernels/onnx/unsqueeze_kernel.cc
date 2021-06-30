#include "ppl/nn/engines/x86/kernels/onnx/unsqueeze_kernel.h"

namespace ppl { namespace nn { namespace x86 {

ppl::common::RetCode UnsqueezeKernel::DoExecute(KernelExecContext* ctx) {
    auto data = ctx->GetInput<TensorImpl>(0);
    auto expanded = ctx->GetOutput<TensorImpl>(0);

    PPLNN_X86_DEBUG_TRACE("Op: %s\n", GetName().c_str());
    PPLNN_X86_DEBUG_TRACE("Input [data]:\n");
    PPL_X86_TENSOR_PRINT_DEBUG_MSG(data);
    PPLNN_X86_DEBUG_TRACE("Output [expanded]:\n");
    PPL_X86_TENSOR_PRINT_DEBUG_MSG(expanded);
    for (uint32_t i = 0; i < param_->axes.size(); ++i) {
        PPLNN_X86_DEBUG_TRACE("axes[%u]: %d\n", i, param_->axes[i]);
    }
    PPLNN_X86_DEBUG_TRACE("isa: %u\n", GetISA());

    if (data->GetEdge()->CalcConsumerCount() == 1 && data->GetType() == TENSORTYPE_NORMAL) {
        expanded->TransferBufferFrom(data);
    } else {
        memcpy(expanded->GetBufferPtr(), data->GetBufferPtr(), data->GetShape().GetBytesIncludingPadding());
    }

    return ppl::common::RC_SUCCESS;
}

}}} // namespace ppl::nn::x86
