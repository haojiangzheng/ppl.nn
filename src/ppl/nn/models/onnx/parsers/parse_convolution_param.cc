#include "ppl/nn/models/onnx/parsers/parse_convolution_param.h"
#include "ppl/nn/models/onnx/utils.h"
namespace ppl { namespace nn { namespace onnx {

ppl::common::RetCode ParseConvolutionParam(const ::onnx::NodeProto& pb_node, void* arg, ir::Node*, ir::GraphTopo*) {
    auto param = static_cast<ppl::nn::common::ConvolutionParam*>(arg);

    param->kernel_shape = utils::GetNodeAttrsByKey<int32_t>(pb_node, "kernel_shape");
    param->dilations = utils::GetNodeAttrsByKey<int32_t>(pb_node, "dilations");
    param->strides = utils::GetNodeAttrsByKey<int32_t>(pb_node, "strides");
    param->pads = utils::GetNodeAttrsByKey<int32_t>(pb_node, "pads");
    param->group = utils::GetNodeAttrByKey(pb_node, "group", 1);
    param->num_output = 0; // set by opcontext
    param->bias_term = 0; // set by opcontext

    uint32_t kernel_dims = param->kernel_shape.size();
    if (kernel_dims == 0) {
        return ppl::common::RC_INVALID_VALUE;
    }

    // if empty, set to default value
    if (param->dilations.size() == 0) {
        param->dilations.resize(kernel_dims, 1);
    }
    if (param->strides.size() == 0) {
        param->strides.resize(kernel_dims, 1);
    }
    if (param->pads.size() == 0) {
        param->pads.resize(kernel_dims * 2, 0);
    }

    if (param->dilations.size() != kernel_dims || param->strides.size() != kernel_dims ||
        param->pads.size() != kernel_dims * 2) {
        return ppl::common::RC_INVALID_VALUE;
    }

    return ppl::common::RC_SUCCESS;
}

}}} // namespace ppl::nn::onnx
