#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_KERNELS_ONNX_CONSTANT_OF_SHAPE_KERNEL_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_KERNELS_ONNX_CONSTANT_OF_SHAPE_KERNEL_H_

#include "ppl/nn/engines/cuda/kernel.h"

#include "ppl/nn/params/onnx/constant_of_shape_param.h"

namespace ppl { namespace nn { namespace cuda {

class ConstantOfShapeKernel : public CudaKernel {
public:
    ConstantOfShapeKernel(const ir::Node* node) : CudaKernel(node) {}

    void SetParam(const ppl::nn::common::ConstantOfShapeParam* p) {
        param_ = p;
    }

private:
    uint64_t CalcTmpBufferSize(const KernelExecContext& ctx) const override;
    ppl::common::RetCode DoExecute(KernelExecContext*) override;

private:
    const ppl::nn::common::ConstantOfShapeParam* param_ = nullptr;
};

}}} // namespace ppl::nn::cuda

#endif
