#include "ppl/nn/engines/cuda/kernel.h"

#include <chrono>

#include "ppl/common/allocator.h"
#include "ppl/nn/common/logger.h"

using namespace ppl::common;

namespace ppl { namespace nn { namespace cuda {

CudaKernel::~CudaKernel() {
#ifdef PPLNN_ENABLE_KERNEL_PROFILING
    if (exec_begin_event_) {
        cudaEventDestroy(exec_begin_event_);
    }
    if (exec_end_event_) {
        cudaEventDestroy(exec_end_event_);
    }
#endif
}

RetCode CudaKernel::Init() {
#ifdef PPLNN_ENABLE_KERNEL_PROFILING
    auto err = cudaEventCreate(&exec_begin_event_);
    if (err != cudaSuccess) {
        LOG(ERROR) << "cudaEventCreate failed: " << cudaGetErrorString(err);
        return RC_OTHER_ERROR;
    }

    err = cudaEventCreate(&exec_end_event_);
    if (err != cudaSuccess) {
        LOG(ERROR) << "cudaEventCreate failed: " << cudaGetErrorString(err);
        return RC_OTHER_ERROR;
    }
#endif

    return RC_SUCCESS;
}

RetCode CudaKernel::BeforeExecute(KernelExecContext* ctx) {
    auto status = Reshape(ctx);
    if (status != RC_SUCCESS) {
        return status;
    }

    for (uint32_t i = 0; i < ctx->GetOutputCount(); ++i) {
        auto tensor = ctx->GetOutput<TensorImpl>(i);
        status = tensor->GetBufferPtr() != nullptr ? RC_SUCCESS : tensor->ReallocBuffer();
        if (status != RC_SUCCESS) {
            LOG(ERROR) << "ReallocBuffer for tensor[" << tensor->GetName() << "] failed: " << GetRetCodeStr(status);
            return status;
        }
    }

    return RC_SUCCESS;
}

#ifdef PPLNN_ENABLE_KERNEL_PROFILING
class CudaTimingGuard final {
public:
    CudaTimingGuard(cudaStream_t stream, cudaEvent_t* begin_event, cudaEvent_t* end_event, bool is_profiling_enabled)
        : is_profiling_enabled_(is_profiling_enabled), end_event_(end_event), stream_(stream) {
        if (is_profiling_enabled) {
            cudaEventRecord(*begin_event, stream);
            stream_ = stream;
        }
    }
    ~CudaTimingGuard() {
        if (is_profiling_enabled_) {
            cudaEventRecord(*end_event_, stream_);
        }
    }

private:
    bool is_profiling_enabled_;
    cudaEvent_t* end_event_;
    cudaStream_t stream_;
};
#endif

bool CudaKernel::CanDoExecute(const KernelExecContext& ctx) const {
    for (uint32_t i = 0; i < ctx.GetInputCount(); ++i) {
        auto tensor = ctx.GetInput<TensorImpl>(i);
        if (!tensor || tensor->GetShape().GetBytesIncludingPadding() == 0) {
            return false;
        }
    }
    return true;
}

RetCode CudaKernel::Execute(KernelExecContext* ctx) {
#ifdef PPLNN_ENABLE_KERNEL_PROFILING
    CudaTimingGuard __timing_guard__(static_cast<CudaDevice*>(GetDevice())->GetStream(), &exec_begin_event_,
                                     &exec_end_event_, ctx->IsProfilingEnabled());
#endif

    auto status = BeforeExecute(ctx);
    if (status != RC_SUCCESS) {
        return status;
    }

#ifndef NDEBUG
    uint32_t total_size = 0;
    LOG(INFO) << "Before execute kernel[" << GetName() << "]";
    for (uint32_t i = 0; i < ctx->GetInputCount(); ++i) {
        auto tensor = ctx->GetInput<TensorImpl>(i);
        if (!tensor) {
            continue;
        }
        auto tensor_size = tensor->GetShape().GetBytesIncludingPadding();
        total_size += tensor_size;
    }
    for (uint32_t i = 0; i < ctx->GetOutputCount(); ++i) {
        auto tensor = ctx->GetOutput<TensorImpl>(i);
        auto tensor_size = tensor->GetShape().GetBytesIncludingPadding();
        LOG(DEBUG) << "tensor size " << tensor_size;
        LOG(DEBUG) << "tensor datatype " << tensor->GetShape().GetDataType() << " tensor dataformat "
                   << tensor->GetShape().GetDataFormat();
        LOG(DEBUG) << "tensor dimcount " << tensor->GetShape().GetDimCount();
        LOG(DEBUG) << "tensor n and c " << tensor->GetShape().GetDim(0) << " " << tensor->GetShape().GetDim(1);
        LOG(DEBUG) << "tensor h and w " << tensor->GetShape().GetDim(2) << " " << tensor->GetShape().GetDim(3);
        total_size += tensor_size;
    }
    auto run_begin_ts = std::chrono::system_clock::now();
#endif

    if (CanDoExecute(*ctx)) {
        status = DoExecute(ctx);
    }

#ifndef NDEBUG
    auto run_end_ts = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(run_end_ts - run_begin_ts);
    LOG(INFO) << "After execute kernel[" << GetName() << "] with running time " << (float)diff.count()
              << " ms and memory cost " << total_size;
#endif

    return status;
}

#ifdef PPLNN_ENABLE_KERNEL_PROFILING
uint64_t CudaKernel::GetExecutionTime() const {
    cudaEventSynchronize(exec_end_event_);
    float ms = 0.0;
    cudaEventElapsedTime(&ms, exec_begin_event_, exec_end_event_);
    return static_cast<uint64_t>(ms * 1000);
}
#endif

}}} // namespace ppl::nn::cuda
