#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_MACROS_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_MACROS_H_

#define CUDA_DEFAULT_ALIGNMENT 64u

#include "ppl/nn/common/logger.h"
#include "ppl/common/stripfilename.h"

#ifndef PPLNN_CUDA_DEBUG_TRACE
#if defined(DEBUG) || !defined(NDEBUG)
#include <stdio.h>
#define PPLNN_CUDA_DEBUG_TRACE(fmt, ...) \
    fprintf(stderr, "T [%s:%u] " fmt, ppl::common::stripfilename(__FILE__), __LINE__, ##__VA_ARGS__)
#else
#define PPLNN_CUDA_DEBUG_TRACE(fmt, ...)
#endif // DEBUG
#endif // Not define PPLNN_CUDA_DEBUG_TRACE

#define PPL_CUDA_TENSOR_PRINT_DEBUG_MSG(X)                                                                        \
    do {                                                                                                          \
        if (X->GetShape().IsScalar()) {                                                                           \
            PPLNN_CUDA_DEBUG_TRACE("Scalar name: %s\n", X->GetName().c_str());                                    \
            PPLNN_CUDA_DEBUG_TRACE("\tdata: %p type: %u\n", X->GetBufferPtr(), X->GetShape().GetDataType());      \
        } else {                                                                                                  \
            PPLNN_CUDA_DEBUG_TRACE("Tensor name: %s\n", X->GetName().c_str());                                    \
            PPLNN_CUDA_DEBUG_TRACE("\tdata: %p type: %u\n", X->GetBufferPtr(), X->GetType());                     \
            PPLNN_CUDA_DEBUG_TRACE("DimCount: %u\n", X->GetShape().GetDimCount());                                \
            for (uint32_t i = 0; i < X->GetShape().GetDimCount(); ++i) {                                          \
                PPLNN_CUDA_DEBUG_TRACE("\tdim[%u]: %u \tpads: [%hu, %hu]\n", i, X->GetShape().GetDim(i),          \
                                       X->GetShape().GetPadding0(i), X->GetShape().GetPadding1(i));               \
            }                                                                                                     \
        }                                                                                                         \
        PPLNN_CUDA_DEBUG_TRACE("DataType: %s\n", ppl::common::GetDataTypeStr(X->GetShape().GetDataType()));       \
        PPLNN_CUDA_DEBUG_TRACE("DataFormat: %s\n", ppl::common::GetDataFormatStr(X->GetShape().GetDataFormat())); \
    } while (0)

#endif
