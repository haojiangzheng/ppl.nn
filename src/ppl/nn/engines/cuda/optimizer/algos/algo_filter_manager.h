#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGO_FILTER_MANAGER_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGO_FILTER_MANAGER_H_

#include "ppl/nn/engines/cuda/optimizer/opt_kernel.h"
#include "ppl/nn/engines/cuda/optimizer/algos/algo_bridge.h"
#include "ppl/nn/engines/cuda/optimizer/algos/algo_concat.h"
#include "ppl/nn/engines/cuda/optimizer/algos/algo_conv.h"
#include "ppl/nn/engines/cuda/optimizer/algos/algo_gemm.h"
#include "ppl/nn/engines/cuda/optimizer/algos/algo_normal.h"

namespace ppl { namespace nn { namespace cuda {

class AlgoFilter {
public:
    uint32_t GetAlgoCount() const {
        return algo_vector_.size();
    }
    Algorithm* GetAlgo(uint32_t idx) const {
        return algo_vector_[idx];
    }
    void AppendAlgo(Algorithm* algo) {
        algo_vector_.push_back(algo);
    }

private:
    std::vector<Algorithm*> algo_vector_;
};

class AlgoFilterManager {
public:
    static AlgoFilterManager* Instance() {
        static AlgoFilterManager mgr;
        return &mgr;
    }

    const AlgoFilter* FindKernel(const std::string& kernel_type) const;

private:
    AlgoFilterManager();

private:
    std::map<std::string, AlgoFilter> type2algo_;
    BridgeAlgorithm bridge_imp_;
    ConcatAlgorithm concat_imp_;
    DepthwiseDirect depthwise_direct_imp_;
    GemmAlgorithm gemm_imp_;
    NormalAlgorithm normal_imp_;
    TuringHMMAImpgemm turing_hmma_imp_;
};

}}} // namespace ppl::nn::cuda

#endif
