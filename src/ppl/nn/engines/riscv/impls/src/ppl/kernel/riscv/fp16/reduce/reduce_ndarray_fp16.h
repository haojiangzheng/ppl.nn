// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef __ST_PPL_KERNEL_RISCV_FP16_REDUCE_REDUCE_NDARRAY_FP16_H_
#define __ST_PPL_KERNEL_RISCV_FP16_REDUCE_REDUCE_NDARRAY_FP16_H_

#include <cstring>
#include "ppl/kernel/riscv/fp16/reduce/reduce_kernel_fp16.h"

namespace ppl { namespace kernel { namespace riscv {

template <reduce_op_type_t op>
static void reduce_ndarray_lastdim_no_reduce_fp16(
    const __fp16* src,
    __fp16* dst,

    const int64_t dim_len)
{
    const int64_t parall_d   = 16;
    const int64_t unroll_len = parall_d * 8;
    const auto vl            = vsetvli(8, RVV_E16, RVV_M1);

    int64_t i = 0;
    for (; i + unroll_len < dim_len; i += unroll_len) {
        vsev_float16xm1(dst + i + 0 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 0 * 8, vl), vlev_float16xm1(dst + i + 0 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 1 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 1 * 8, vl), vlev_float16xm1(dst + i + 1 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 2 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 2 * 8, vl), vlev_float16xm1(dst + i + 2 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 3 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 3 * 8, vl), vlev_float16xm1(dst + i + 3 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 4 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 4 * 8, vl), vlev_float16xm1(dst + i + 4 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 5 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 5 * 8, vl), vlev_float16xm1(dst + i + 5 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 6 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 6 * 8, vl), vlev_float16xm1(dst + i + 6 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 7 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 7 * 8, vl), vlev_float16xm1(dst + i + 7 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 8 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 8 * 8, vl), vlev_float16xm1(dst + i + 8 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 9 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 9 * 8, vl), vlev_float16xm1(dst + i + 9 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 10 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 10 * 8, vl), vlev_float16xm1(dst + i + 10 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 11 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 11 * 8, vl), vlev_float16xm1(dst + i + 11 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 12 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 12 * 8, vl), vlev_float16xm1(dst + i + 12 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 13 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 13 * 8, vl), vlev_float16xm1(dst + i + 13 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 14 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 14 * 8, vl), vlev_float16xm1(dst + i + 14 * 8, vl)), vl);
        vsev_float16xm1(dst + i + 15 * 8, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 15 * 8, vl), vlev_float16xm1(dst + i + 15 * 8, vl)), vl);
    }
    for (; i < dim_len; i += 8) {
        vsev_float16xm1(dst + i, reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i, vl), vlev_float16xm1(dst + i, vl)), vl);
    }
}

template <reduce_op_type_t op>
static void reduce_ndarray_lastdim_reduce_fp16(
    const __fp16* src,
    __fp16* dst,

    const int64_t dim_len)
{
    const auto vl         = vsetvli(8, RVV_E16, RVV_M1);
    const __fp16 init_val = reduce_init_val_fp16<op>();
    float16xm1_t v_tmp0   = vfmvvf_float16xm1(init_val, vl);
    float16xm1_t v_tmp1   = v_tmp0;
    float16xm1_t v_tmp2   = v_tmp0;
    float16xm1_t v_tmp3   = v_tmp0;
    float16xm1_t v_tmp4   = v_tmp0;
    float16xm1_t v_tmp5   = v_tmp0;
    float16xm1_t v_tmp6   = v_tmp0;
    float16xm1_t v_tmp7   = v_tmp0;
    float16xm1_t v_tmp8   = v_tmp0;
    float16xm1_t v_tmp9   = v_tmp0;
    float16xm1_t v_tmp10  = v_tmp0;
    float16xm1_t v_tmp11  = v_tmp0;
    float16xm1_t v_tmp12  = v_tmp0;
    float16xm1_t v_tmp13  = v_tmp0;
    float16xm1_t v_tmp14  = v_tmp0;
    float16xm1_t v_tmp15  = v_tmp0;

    float16xm1_t v_tmp16 = v_tmp0;

    const int64_t parall_d   = 16;
    const int64_t unroll_len = parall_d * 8;

    int64_t i = 0;
    for (; i + unroll_len < dim_len; i += unroll_len) {
        v_tmp0  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 0 * 8, vl), v_tmp0);
        v_tmp1  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 1 * 8, vl), v_tmp1);
        v_tmp2  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 2 * 8, vl), v_tmp2);
        v_tmp3  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 3 * 8, vl), v_tmp3);
        v_tmp4  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 4 * 8, vl), v_tmp4);
        v_tmp5  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 5 * 8, vl), v_tmp5);
        v_tmp6  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 6 * 8, vl), v_tmp6);
        v_tmp7  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 7 * 8, vl), v_tmp7);
        v_tmp8  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 8 * 8, vl), v_tmp8);
        v_tmp9  = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 9 * 8, vl), v_tmp9);
        v_tmp10 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 10 * 8, vl), v_tmp10);
        v_tmp11 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 11 * 8, vl), v_tmp11);
        v_tmp12 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 12 * 8, vl), v_tmp12);
        v_tmp13 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 13 * 8, vl), v_tmp13);
        v_tmp14 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 14 * 8, vl), v_tmp14);
        v_tmp15 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i + 15 * 8, vl), v_tmp15);
    }
    for (; i < dim_len; i += 8) {
        v_tmp16 = reduce_vector_kernel_fp16<op>(vlev_float16xm1(src + i, vl), v_tmp16);
    }

    if (dim_len >= unroll_len) {
        v_tmp0  = reduce_vector_kernel_fp16<op>(v_tmp0, v_tmp1);
        v_tmp2  = reduce_vector_kernel_fp16<op>(v_tmp2, v_tmp3);
        v_tmp4  = reduce_vector_kernel_fp16<op>(v_tmp4, v_tmp5);
        v_tmp6  = reduce_vector_kernel_fp16<op>(v_tmp6, v_tmp7);
        v_tmp8  = reduce_vector_kernel_fp16<op>(v_tmp8, v_tmp9);
        v_tmp10 = reduce_vector_kernel_fp16<op>(v_tmp10, v_tmp11);
        v_tmp12 = reduce_vector_kernel_fp16<op>(v_tmp12, v_tmp13);
        v_tmp14 = reduce_vector_kernel_fp16<op>(v_tmp14, v_tmp15);

        v_tmp0  = reduce_vector_kernel_fp16<op>(v_tmp0, v_tmp2);
        v_tmp4  = reduce_vector_kernel_fp16<op>(v_tmp4, v_tmp6);
        v_tmp8  = reduce_vector_kernel_fp16<op>(v_tmp8, v_tmp10);
        v_tmp12 = reduce_vector_kernel_fp16<op>(v_tmp12, v_tmp14);

        v_tmp0 = reduce_vector_kernel_fp16<op>(v_tmp0, v_tmp4);
        v_tmp8 = reduce_vector_kernel_fp16<op>(v_tmp8, v_tmp12);

        v_tmp0 = reduce_vector_kernel_fp16<op>(v_tmp0, v_tmp8);
    }
    v_tmp16           = reduce_vector_kernel_fp16<op>(v_tmp0, v_tmp16);
    __fp16 reduce_val = init_val;
    reduce_val        = reduce_scalar_kernel_fp16<op>(reduce_vector_all_lanes_kernel_fp16<op>(v_tmp16), reduce_val);

    dst[0] = reduce_scalar_kernel_fp16<op>(dst[0], reduce_val);
}

template <reduce_op_type_t op>
static void reduce_ndarray_recursive_fp16(
    const __fp16* src,
    __fp16* dst,

    const ppl::common::TensorShape* src_shape,
    const ppl::common::TensorShape* dst_shape,
    const int64_t dim_idx,
    const int64_t* inc_src,
    const int64_t* inc_dst)
{
    const int64_t len = src_shape->GetDim(dim_idx);
    if (dim_idx == src_shape->GetDimCount() - 1) {
        if (src_shape->GetDim(dim_idx) == dst_shape->GetDim(dim_idx)) {
            reduce_ndarray_lastdim_no_reduce_fp16<op>(src, dst, src_shape->GetDim(dim_idx));
        } else {
            reduce_ndarray_lastdim_reduce_fp16<op>(src, dst, src_shape->GetDim(dim_idx));
        }
    } else {
        for (int64_t i = 0; i < len; i++) {
            const __fp16* src_ = src + i * inc_src[dim_idx];
            __fp16* dst_       = dst + i * inc_dst[dim_idx];
            reduce_ndarray_recursive_fp16<op>(src_, dst_, src_shape, dst_shape, dim_idx + 1, inc_src, inc_dst);
        }
    }
}

template <reduce_op_type_t op>
ppl::common::RetCode reduce_ndarray_fp16(
    const __fp16* src,
    __fp16* dst,

    const ppl::common::TensorShape* src_shape,
    const ppl::common::TensorShape* dst_shape,
    const int32_t* axes,
    const int32_t num_axes)
{
    if (src_shape->GetDimCount() > PPL_RISCV_TENSOR_MAX_DIMS()) {
        return ppl::common::RC_UNSUPPORTED;
    }

    ppl::common::TensorShape& padded_dst_shape = *(new ppl::common::TensorShape(*src_shape));
    for (int64_t i = 0; i < num_axes; i++) {
        padded_dst_shape.SetDim(axes[i], 1);
    }

    reduce_preprocess_fp16<op>(dst, padded_dst_shape.CalcElementsIncludingPadding());

    int64_t dim_count                            = padded_dst_shape.GetDimCount();
    int64_t inc_src[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    int64_t inc_dst[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    int64_t stride_src                           = 1;
    int64_t stride_dst                           = 1;

    for (int64_t i = dim_count - 1; i >= 0; i--) {
        inc_src[i] = src_shape->GetDim(i) == 1 ? 0 : stride_src;
        inc_dst[i] = padded_dst_shape.GetDim(i) == 1 ? 0 : stride_dst;

        stride_src *= src_shape->GetDim(i);
        stride_dst *= padded_dst_shape.GetDim(i);
    }

    reduce_ndarray_recursive_fp16<op>(src, dst, src_shape, &padded_dst_shape, 0, inc_src, inc_dst);

    int64_t reduce_factor = 1;
    for (int64_t i = 0; i < dim_count; i++) {
        reduce_factor *= src_shape->GetDim(i) / padded_dst_shape.GetDim(i);
    }
    reduce_postprocess_fp16<op>(dst, padded_dst_shape.CalcElementsIncludingPadding(), reduce_factor);

    delete &padded_dst_shape;

    return ppl::common::RC_SUCCESS;
}

}}}; // namespace ppl::kernel::riscv

#endif //  __ST_PPL_KERNEL_RISCV_FP16_REDUCE_REDUCE_NDARRAY_FP16_H_
