#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_PARAMS_CONV_EXTRA_PARAM_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_PARAMS_CONV_EXTRA_PARAM_H_

#include <set>
#include <string>

#include "ppl/nn/engines/cuda/cuda_device.h"
#include "ppl/nn/oputils/onnx/reshape_convolution.h"
#include "ppl/nn/engines/cuda/optimizer/opt_kernel.h"
#include "cudakernel/nn/conv/conv_fp16.h"
#include "cudakernel/nn/conv/depthwise.h"
#include "cudakernel/nn/conv/group_padding.h"

#define FLT_MAX 3e+38F

using namespace ppl::common;

namespace ppl { namespace nn { namespace cuda {
struct ClipParam {
    float min_val = -FLT_MAX;
    float max_val = FLT_MAX;
};

struct ConvFusionInfo {
    std::vector<std::string> types; // max fuse relu + add + relu right now
    std::vector<uint32_t> input_ind; // save fused kernel's input index
    std::vector<void*> fuse_attrs; // save fused kernel's attributes
    int channel_size = -1; // save total channel size for concat
    int channel_offset = -1; // save output offset if we fuse concat
    int concat_edge_id = -1; // save concat output edge id
};

struct ConvAlgoInfo {
    std::string algo_type = "";
    unsigned int kernel_index;
    unsigned int splitk = 1;
    unsigned int splitf = 1;
    bool is_initializer_weight = 1;
};

struct ConvExtraParam {
    ConvAlgoInfo algo_info;
    ConvFusionInfo fuse_info;
};

struct CudaConvParam {
    ppl::nn::common::ConvolutionParam param;
    ConvExtraParam extra_param;
};

ppl::common::RetCode ConvertToForwardConvParam(const TensorShape& shape_in0, const TensorShape& shape_in1,
                                               const TensorShape& shape_out,
                                               ppl::nn::common::ConvolutionParam normal_param,
                                               conv_param_t& conv_param);

ppl::common::RetCode ConvertToEmptyFuseParam(fuse_param_t& fuse_param);

ppl::common::RetCode ConvertToForwardFuseParam(InputOutputInfo* info, CudaDevice* devive, ConvFusionInfo fuse_info,
                                               fuse_param_t& fuse_param);
}}} // namespace ppl::nn::cuda

#endif
