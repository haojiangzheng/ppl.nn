#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGO_NORMAL_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGO_NORMAL_H_

#include "ppl/nn/engines/cuda/optimizer/algos/algorithm.h"

using namespace ppl::common;

namespace ppl { namespace nn { namespace cuda {

class NormalAlgorithm : public Algorithm {
public:
    NormalAlgorithm() {
        std::set<dataformat_t> ndarray{DATAFORMAT_NDARRAY};
        std::set<dataformat_t> nhwc{DATAFORMAT_NHWC};

        ndarray_formats_.emplace(DATAFORMAT_NDARRAY, ndarray);
        nhwc_formats_.emplace(DATAFORMAT_NHWC, nhwc);
        inherited_formats_.emplace(DATAFORMAT_NDARRAY, ndarray);
        inherited_formats_.emplace(DATAFORMAT_NHWC, nhwc);
        arbitrary_formats_.emplace(DATAFORMAT_NDARRAY, ndarray);
        arbitrary_formats_.emplace(DATAFORMAT_NHWC, ndarray);
    }

    void GetAttrParam(void*& param) override {
        return;
    };
    void DeleteAttrParam(void*& param) override {
        return;
    };
    const std::map<dataformat_t, std::set<dataformat_t>> Getformats(const std::string& type_name) override {
        if (inherited_set_.find(type_name) != inherited_set_.end()) {
            return inherited_formats_;
        }
        if (arbitrary_set_.find(type_name) != arbitrary_set_.end()) {
            return arbitrary_formats_;
        }
        if (nhwc_set_.find(type_name) != nhwc_set_.end()) {
            return nhwc_formats_;
        }
        return ndarray_formats_;
    }

    const double ExcuteTimer(ir::Node* node, OptKernelOptions& options) override;
    RetCode ModifyParam(const ir::Node*, OptKernelOptions& options) override {
        return RC_SUCCESS;
    }
    void ReshapeOnEdges(const ir::Node* node, std::map<edgeid_t, std::unique_ptr<TensorImpl>>* tensors,
                        dataformat_t input_format, dataformat_t output_format) override;

private:
    std::map<dataformat_t, std::set<dataformat_t>> ndarray_formats_;
    std::map<dataformat_t, std::set<dataformat_t>> nhwc_formats_;
    std::map<dataformat_t, std::set<dataformat_t>> inherited_formats_;
    std::map<dataformat_t, std::set<dataformat_t>> arbitrary_formats_;
    std::set<std::string> inherited_set_{"Add",
                                         "Mul",
                                         "Div",
                                         "Sub",
                                         "Relu",
                                         "PRelu",
                                         "Clip",
                                         "LeakyRelu",
                                         "Cast",
                                         "MaxPool",
                                         "GlobalMaxPool",
                                         "AveragePool",
                                         "GlobalAveragePool",
                                         "BatchNormalization",
                                         "Slice",
                                         "Split",
                                         "Sigmoid"};
    std::set<std::string> arbitrary_set_{"Shape"};
    std::set<std::string> nhwc_set_{};
};

}}} // namespace ppl::nn::cuda

#endif
