#ifndef __ST_PPL_KERNEL_X86_FP32_CONV2D_DIRECT_NDARRAY_AVX512_CONV2D_N16CX_DIRECT_NDARRAY_BLK1X14_KERNEL_FP32_AVX512_H_
#define __ST_PPL_KERNEL_X86_FP32_CONV2D_DIRECT_NDARRAY_AVX512_CONV2D_N16CX_DIRECT_NDARRAY_BLK1X14_KERNEL_FP32_AVX512_H_

#include <immintrin.h>

#include "ppl/kernel/x86/fp32/conv2d/direct_ndarray/avx512/conv2d_n16cx_direct_ndarray_kernel_fp32_avx512.h"

namespace ppl { namespace kernel { namespace x86 {

template <bool nt_store, int32_t oc_len, int32_t w_len>
void conv2d_n16cx_direct_ndarray_fp32_avx512_blk1x14_kernel(
    const int64_t *priv_param,
    const int64_t *shar_param)
{
#define KW_COMPUTE_STEP() do {\
    if (oc_len > 0 * OC_DT_BLK()) zmm28 = _mm512_loadu_ps(k_flt + 0 * flt_ocb_stride);\
    if (oc_len > 1 * OC_DT_BLK()) zmm29 = _mm512_loadu_ps(k_flt + 1 * flt_ocb_stride);\
    if (w_len > 0) {\
        zmm30 = _mm512_set1_ps(k_src[0 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm0  = _mm512_fmadd_ps(zmm28, zmm30, zmm0);\
        if (oc_len > 1 * OC_DT_BLK()) zmm14 = _mm512_fmadd_ps(zmm29, zmm30, zmm14);\
    }\
    if (w_len > 1) {\
        zmm31 = _mm512_set1_ps(k_src[1 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm1  = _mm512_fmadd_ps(zmm28, zmm31, zmm1);\
        if (oc_len > 1 * OC_DT_BLK()) zmm15 = _mm512_fmadd_ps(zmm29, zmm31, zmm15);\
    }\
    if (w_len > 2) {\
        zmm30 = _mm512_set1_ps(k_src[2 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm2  = _mm512_fmadd_ps(zmm28, zmm30, zmm2);\
        if (oc_len > 1 * OC_DT_BLK()) zmm16 = _mm512_fmadd_ps(zmm29, zmm30, zmm16);\
    }\
    if (w_len > 3) {\
        zmm31 = _mm512_set1_ps(k_src[3 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm3  = _mm512_fmadd_ps(zmm28, zmm31, zmm3);\
        if (oc_len > 1 * OC_DT_BLK()) zmm17 = _mm512_fmadd_ps(zmm29, zmm31, zmm17);\
    }\
    if (w_len > 4) {\
        zmm30 = _mm512_set1_ps(k_src[4 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm4  = _mm512_fmadd_ps(zmm28, zmm30, zmm4);\
        if (oc_len > 1 * OC_DT_BLK()) zmm18 = _mm512_fmadd_ps(zmm29, zmm30, zmm18);\
    }\
    if (w_len > 5) {\
        zmm31 = _mm512_set1_ps(k_src[5 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm5  = _mm512_fmadd_ps(zmm28, zmm31, zmm5);\
        if (oc_len > 1 * OC_DT_BLK()) zmm19 = _mm512_fmadd_ps(zmm29, zmm31, zmm19);\
    }\
    if (w_len > 6) {\
        zmm30 = _mm512_set1_ps(k_src[6 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm6  = _mm512_fmadd_ps(zmm28, zmm30, zmm6);\
        if (oc_len > 1 * OC_DT_BLK()) zmm20 = _mm512_fmadd_ps(zmm29, zmm30, zmm20);\
    }\
    if (w_len > 6) {\
        zmm31 = _mm512_set1_ps(k_src[7 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm7  = _mm512_fmadd_ps(zmm28, zmm31, zmm7);\
        if (oc_len > 1 * OC_DT_BLK()) zmm21 = _mm512_fmadd_ps(zmm29, zmm31, zmm21);\
    }\
    if (w_len > 8) {\
        zmm30 = _mm512_set1_ps(k_src[8 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm8  = _mm512_fmadd_ps(zmm28, zmm30, zmm8);\
        if (oc_len > 1 * OC_DT_BLK()) zmm22 = _mm512_fmadd_ps(zmm29, zmm30, zmm22);\
    }\
    if (w_len > 9) {\
        zmm31 = _mm512_set1_ps(k_src[9 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm9  = _mm512_fmadd_ps(zmm28, zmm31, zmm9);\
        if (oc_len > 1 * OC_DT_BLK()) zmm23 = _mm512_fmadd_ps(zmm29, zmm31, zmm23);\
    }\
    if (w_len > 10) {\
        zmm30 = _mm512_set1_ps(k_src[10 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm10 = _mm512_fmadd_ps(zmm28, zmm30, zmm10);\
        if (oc_len > 1 * OC_DT_BLK()) zmm24 = _mm512_fmadd_ps(zmm29, zmm30, zmm24);\
    }\
    if (w_len > 11) {\
        zmm31 = _mm512_set1_ps(k_src[11 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm11 = _mm512_fmadd_ps(zmm28, zmm31, zmm11);\
        if (oc_len > 1 * OC_DT_BLK()) zmm25 = _mm512_fmadd_ps(zmm29, zmm31, zmm25);\
    }\
    if (w_len > 12) {\
        zmm30 = _mm512_set1_ps(k_src[12 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm12 = _mm512_fmadd_ps(zmm28, zmm30, zmm12);\
        if (oc_len > 1 * OC_DT_BLK()) zmm26 = _mm512_fmadd_ps(zmm29, zmm30, zmm26);\
    }\
    if (w_len > 13) {\
        zmm31 = _mm512_set1_ps(k_src[13 * stride_w]);\
        if (oc_len > 0 * OC_DT_BLK()) zmm13 = _mm512_fmadd_ps(zmm28, zmm31, zmm13);\
        if (oc_len > 1 * OC_DT_BLK()) zmm27 = _mm512_fmadd_ps(zmm29, zmm31, zmm27);\
    }\
    k_flt += OC_DT_BLK();\
    k_src += 1;\
} while (0)

    __m512 zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7;
    __m512 zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15;
    __m512 zmm16, zmm17, zmm18, zmm19, zmm20, zmm21, zmm22, zmm23;
    __m512 zmm24, zmm25, zmm26, zmm27, zmm28, zmm29, zmm30, zmm31;

    const int64_t kernel_h = shar_param[KH_IDX()];
    const int64_t kernel_w = shar_param[KW_IDX()];
    const int64_t stride_w = shar_param[SW_IDX()];
    const int64_t src_c_stride = shar_param[SRC_C_STRIDE_IDX()];
    const int64_t src_h_stride = shar_param[SRC_H_STRIDE_IDX()];
    const int64_t flt_ocb_stride = shar_param[FLT_OCB_STRIDE_IDX()];
    const int64_t kernel_flags = shar_param[FLAGS_IDX()];
    const int64_t kh_start = priv_param[KH_START_IDX()];
    const int64_t kh_end = priv_param[KH_END_IDX()];

    const float *src = PICK_PARAM(const float*, priv_param, SRC_IDX());
    const float *his = PICK_PARAM(const float*, priv_param, HIS_IDX());
    float *dst       = PICK_PARAM(float*, priv_param, DST_IDX());
    int64_t ow       = priv_param[OW_IDX()];
    do {
        if (kernel_flags & KERNEL_FLAG_LD_BIAS()) {
            const float* bias = PICK_PARAM(const float*, priv_param, BIAS_IDX());
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) zmm0 = _mm512_loadu_ps(bias + 0 * OC_DT_BLK());
                if (w_len > 1) zmm1 = zmm0;
                if (w_len > 2) zmm2 = zmm0;
                if (w_len > 3) zmm3 = zmm0;
                if (w_len > 4) zmm4 = zmm0;
                if (w_len > 5) zmm5 = zmm0;
                if (w_len > 6) zmm6 = zmm0;
                if (w_len > 7) zmm7 = zmm0;
                if (w_len > 8) zmm8 = zmm0;
                if (w_len > 9) zmm9 = zmm0;
                if (w_len > 10) zmm10 = zmm0;
                if (w_len > 11) zmm11 = zmm0;
                if (w_len > 12) zmm12 = zmm0;
                if (w_len > 13) zmm13 = zmm0;
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                if (w_len > 0) zmm14 = _mm512_loadu_ps(bias + 1 * OC_DT_BLK());
                if (w_len > 1) zmm15 = zmm14;
                if (w_len > 2) zmm16 = zmm14;
                if (w_len > 3) zmm17 = zmm14;
                if (w_len > 4) zmm18 = zmm14;
                if (w_len > 5) zmm19 = zmm14;
                if (w_len > 6) zmm20 = zmm14;
                if (w_len > 7) zmm21 = zmm14;
                if (w_len > 8) zmm22 = zmm14;
                if (w_len > 9) zmm23 = zmm14;
                if (w_len > 10) zmm24 = zmm14;
                if (w_len > 11) zmm25 = zmm14;
                if (w_len > 12) zmm26 = zmm14;
                if (w_len > 13) zmm27 = zmm14;
            }
        } else {
            const float *l_his = his;
            const int64_t his_ocb_stride = shar_param[HIS_OCB_STRIDE_IDX()];
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) zmm0 = _mm512_loadu_ps(l_his + 0 * OC_DT_BLK());
                if (w_len > 1) zmm1 = _mm512_loadu_ps(l_his + 1 * OC_DT_BLK());
                if (w_len > 2) zmm2 = _mm512_loadu_ps(l_his + 2 * OC_DT_BLK());
                if (w_len > 3) zmm3 = _mm512_loadu_ps(l_his + 3 * OC_DT_BLK());
                if (w_len > 4) zmm4 = _mm512_loadu_ps(l_his + 4 * OC_DT_BLK());
                if (w_len > 5) zmm5 = _mm512_loadu_ps(l_his + 5 * OC_DT_BLK());
                if (w_len > 6) zmm6 = _mm512_loadu_ps(l_his + 6 * OC_DT_BLK());
                if (w_len > 7) zmm7 = _mm512_loadu_ps(l_his + 7 * OC_DT_BLK());
                if (w_len > 8) zmm8 = _mm512_loadu_ps(l_his + 8 * OC_DT_BLK());
                if (w_len > 9) zmm9 = _mm512_loadu_ps(l_his + 9 * OC_DT_BLK());
                if (w_len > 10) zmm10 = _mm512_loadu_ps(l_his + 10 * OC_DT_BLK());
                if (w_len > 11) zmm11 = _mm512_loadu_ps(l_his + 11 * OC_DT_BLK());
                if (w_len > 12) zmm12 = _mm512_loadu_ps(l_his + 12 * OC_DT_BLK());
                if (w_len > 13) zmm13 = _mm512_loadu_ps(l_his + 13 * OC_DT_BLK());
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                l_his += his_ocb_stride;
                if (w_len > 0) zmm14 = _mm512_loadu_ps(l_his + 0 * OC_DT_BLK());
                if (w_len > 1) zmm15 = _mm512_loadu_ps(l_his + 1 * OC_DT_BLK());
                if (w_len > 2) zmm16 = _mm512_loadu_ps(l_his + 2 * OC_DT_BLK());
                if (w_len > 3) zmm17 = _mm512_loadu_ps(l_his + 3 * OC_DT_BLK());
                if (w_len > 4) zmm18 = _mm512_loadu_ps(l_his + 4 * OC_DT_BLK());
                if (w_len > 5) zmm19 = _mm512_loadu_ps(l_his + 5 * OC_DT_BLK());
                if (w_len > 6) zmm20 = _mm512_loadu_ps(l_his + 6 * OC_DT_BLK());
                if (w_len > 7) zmm21 = _mm512_loadu_ps(l_his + 7 * OC_DT_BLK());
                if (w_len > 8) zmm22 = _mm512_loadu_ps(l_his + 8 * OC_DT_BLK());
                if (w_len > 9) zmm23 = _mm512_loadu_ps(l_his + 9 * OC_DT_BLK());
                if (w_len > 10) zmm24 = _mm512_loadu_ps(l_his + 10 * OC_DT_BLK());
                if (w_len > 11) zmm25 = _mm512_loadu_ps(l_his + 11 * OC_DT_BLK());
                if (w_len > 12) zmm26 = _mm512_loadu_ps(l_his + 12 * OC_DT_BLK());
                if (w_len > 13) zmm27 = _mm512_loadu_ps(l_his + 13 * OC_DT_BLK());
            }
        }

        if (kernel_flags & KERNEL_FLAG_AD_BIAS()) {
            const float* bias = PICK_PARAM(const float*, priv_param, BIAS_IDX());
            if (oc_len > 0 * OC_DT_BLK()) {
                zmm30 = _mm512_loadu_ps(bias + 0 * OC_DT_BLK());
                if (w_len > 0) zmm0 = _mm512_add_ps(zmm30, zmm0);
                if (w_len > 1) zmm1 = _mm512_add_ps(zmm30, zmm1);
                if (w_len > 2) zmm2 = _mm512_add_ps(zmm30, zmm2);
                if (w_len > 3) zmm3 = _mm512_add_ps(zmm30, zmm3);
                if (w_len > 4) zmm4 = _mm512_add_ps(zmm30, zmm4);
                if (w_len > 5) zmm5 = _mm512_add_ps(zmm30, zmm5);
                if (w_len > 6) zmm6 = _mm512_add_ps(zmm30, zmm6);
                if (w_len > 7) zmm7 = _mm512_add_ps(zmm30, zmm7);
                if (w_len > 8) zmm8 = _mm512_add_ps(zmm30, zmm8);
                if (w_len > 9) zmm9 = _mm512_add_ps(zmm30, zmm9);
                if (w_len > 10) zmm10 = _mm512_add_ps(zmm30, zmm10);
                if (w_len > 11) zmm11 = _mm512_add_ps(zmm30, zmm11);
                if (w_len > 12) zmm12 = _mm512_add_ps(zmm30, zmm12);
                if (w_len > 13) zmm13 = _mm512_add_ps(zmm30, zmm13);
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                zmm31 = _mm512_loadu_ps(bias + 1 * OC_DT_BLK());
                if (w_len > 0) zmm14 = _mm512_add_ps(zmm31, zmm14);
                if (w_len > 1) zmm15 = _mm512_add_ps(zmm31, zmm15);
                if (w_len > 2) zmm16 = _mm512_add_ps(zmm31, zmm16);
                if (w_len > 3) zmm17 = _mm512_add_ps(zmm31, zmm17);
                if (w_len > 4) zmm18 = _mm512_add_ps(zmm31, zmm18);
                if (w_len > 5) zmm19 = _mm512_add_ps(zmm31, zmm19);
                if (w_len > 6) zmm20 = _mm512_add_ps(zmm31, zmm20);
                if (w_len > 7) zmm21 = _mm512_add_ps(zmm31, zmm21);
                if (w_len > 8) zmm22 = _mm512_add_ps(zmm31, zmm22);
                if (w_len > 9) zmm23 = _mm512_add_ps(zmm31, zmm23);
                if (w_len > 10) zmm24 = _mm512_add_ps(zmm31, zmm24);
                if (w_len > 11) zmm25 = _mm512_add_ps(zmm31, zmm25);
                if (w_len > 12) zmm26 = _mm512_add_ps(zmm31, zmm26);
                if (w_len > 13) zmm27 = _mm512_add_ps(zmm31, zmm27);
            }
        }
        
        const float *ic_src = src + kh_start * src_h_stride;
        const float *ic_flt = PICK_PARAM(const float*, priv_param, FLT_IDX()) + kh_start * kernel_w * OC_DT_BLK();
        int64_t channels    = shar_param[CHANNELS_IDX()];
        do {
            const float *k_src = ic_src;
            const float *k_flt = ic_flt;
            for (int64_t kh = kh_start; kh < kh_end; ++kh) {
                for (int64_t kw = 0; kw < kernel_w; ++kw) {
                    KW_COMPUTE_STEP();
                }
                k_src += src_h_stride - kernel_w;
            }
            ic_flt += kernel_h * kernel_w * OC_DT_BLK();
            ic_src += src_c_stride;
            channels -= 1;
        } while (channels > 0);
        
        if (kernel_flags & (KERNEL_FLAG_RELU() | KERNEL_FLAG_RELU6())) {
            zmm30 = _mm512_setzero_ps();
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) zmm0 = _mm512_max_ps(zmm0, zmm30);
                if (w_len > 1) zmm1 = _mm512_max_ps(zmm1, zmm30);
                if (w_len > 2) zmm2 = _mm512_max_ps(zmm2, zmm30);
                if (w_len > 3) zmm3 = _mm512_max_ps(zmm3, zmm30);
                if (w_len > 4) zmm4 = _mm512_max_ps(zmm4, zmm30);
                if (w_len > 5) zmm5 = _mm512_max_ps(zmm5, zmm30);
                if (w_len > 6) zmm6 = _mm512_max_ps(zmm6, zmm30);
                if (w_len > 7) zmm7 = _mm512_max_ps(zmm7, zmm30);
                if (w_len > 8) zmm8 = _mm512_max_ps(zmm8, zmm30);
                if (w_len > 9) zmm9 = _mm512_max_ps(zmm9, zmm30);
                if (w_len > 10) zmm10 = _mm512_max_ps(zmm10, zmm30);
                if (w_len > 11) zmm11 = _mm512_max_ps(zmm11, zmm30);
                if (w_len > 12) zmm12 = _mm512_max_ps(zmm12, zmm30);
                if (w_len > 13) zmm13 = _mm512_max_ps(zmm13, zmm30);
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                if (w_len > 0) zmm14 = _mm512_max_ps(zmm14, zmm30);
                if (w_len > 1) zmm15 = _mm512_max_ps(zmm15, zmm30);
                if (w_len > 2) zmm16 = _mm512_max_ps(zmm16, zmm30);
                if (w_len > 3) zmm17 = _mm512_max_ps(zmm17, zmm30);
                if (w_len > 4) zmm18 = _mm512_max_ps(zmm18, zmm30);
                if (w_len > 5) zmm19 = _mm512_max_ps(zmm19, zmm30);
                if (w_len > 6) zmm20 = _mm512_max_ps(zmm20, zmm30);
                if (w_len > 7) zmm21 = _mm512_max_ps(zmm21, zmm30);
                if (w_len > 8) zmm22 = _mm512_max_ps(zmm22, zmm30);
                if (w_len > 9) zmm23 = _mm512_max_ps(zmm23, zmm30);
                if (w_len > 10) zmm24 = _mm512_max_ps(zmm24, zmm30);
                if (w_len > 11) zmm25 = _mm512_max_ps(zmm25, zmm30);
                if (w_len > 12) zmm26 = _mm512_max_ps(zmm26, zmm30);
                if (w_len > 13) zmm27 = _mm512_max_ps(zmm27, zmm30);
            }
        }
        if (kernel_flags & KERNEL_FLAG_RELU6()) {
            zmm31 = _mm512_set1_ps(6.0f);
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) zmm0 = _mm512_min_ps(zmm0, zmm31);
                if (w_len > 1) zmm1 = _mm512_min_ps(zmm1, zmm31);
                if (w_len > 2) zmm2 = _mm512_min_ps(zmm2, zmm31);
                if (w_len > 3) zmm3 = _mm512_min_ps(zmm3, zmm31);
                if (w_len > 4) zmm4 = _mm512_min_ps(zmm4, zmm31);
                if (w_len > 5) zmm5 = _mm512_min_ps(zmm5, zmm31);
                if (w_len > 6) zmm6 = _mm512_min_ps(zmm6, zmm31);
                if (w_len > 7) zmm7 = _mm512_min_ps(zmm7, zmm31);
                if (w_len > 8) zmm8 = _mm512_min_ps(zmm8, zmm31);
                if (w_len > 9) zmm9 = _mm512_min_ps(zmm9, zmm31);
                if (w_len > 10) zmm10 = _mm512_min_ps(zmm10, zmm31);
                if (w_len > 11) zmm11 = _mm512_min_ps(zmm11, zmm31);
                if (w_len > 12) zmm12 = _mm512_min_ps(zmm12, zmm31);
                if (w_len > 13) zmm13 = _mm512_min_ps(zmm13, zmm31);
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                if (w_len > 0) zmm14 = _mm512_min_ps(zmm14, zmm31);
                if (w_len > 1) zmm15 = _mm512_min_ps(zmm15, zmm31);
                if (w_len > 2) zmm16 = _mm512_min_ps(zmm16, zmm31);
                if (w_len > 3) zmm17 = _mm512_min_ps(zmm17, zmm31);
                if (w_len > 4) zmm18 = _mm512_min_ps(zmm18, zmm31);
                if (w_len > 5) zmm19 = _mm512_min_ps(zmm19, zmm31);
                if (w_len > 6) zmm20 = _mm512_min_ps(zmm20, zmm31);
                if (w_len > 7) zmm21 = _mm512_min_ps(zmm21, zmm31);
                if (w_len > 8) zmm22 = _mm512_min_ps(zmm22, zmm31);
                if (w_len > 9) zmm23 = _mm512_min_ps(zmm23, zmm31);
                if (w_len > 10) zmm24 = _mm512_min_ps(zmm24, zmm31);
                if (w_len > 11) zmm25 = _mm512_min_ps(zmm25, zmm31);
                if (w_len > 12) zmm26 = _mm512_min_ps(zmm26, zmm31);
                if (w_len > 13) zmm27 = _mm512_min_ps(zmm27, zmm31);
            }
        }

        if (nt_store) {
            float* l_dst = dst;
            const int64_t dst_ocb_stride = shar_param[DST_OCB_STRIDE_IDX()];
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) _mm512_stream_ps(l_dst + 0 * OC_DT_BLK(), zmm0);
                if (w_len > 1) _mm512_stream_ps(l_dst + 1 * OC_DT_BLK(), zmm1);
                if (w_len > 2) _mm512_stream_ps(l_dst + 2 * OC_DT_BLK(), zmm2);
                if (w_len > 3) _mm512_stream_ps(l_dst + 3 * OC_DT_BLK(), zmm3);
                if (w_len > 4) _mm512_stream_ps(l_dst + 4 * OC_DT_BLK(), zmm4);
                if (w_len > 5) _mm512_stream_ps(l_dst + 5 * OC_DT_BLK(), zmm5);
                if (w_len > 6) _mm512_stream_ps(l_dst + 6 * OC_DT_BLK(), zmm6);
                if (w_len > 7) _mm512_stream_ps(l_dst + 7 * OC_DT_BLK(), zmm7);
                if (w_len > 8) _mm512_stream_ps(l_dst + 8 * OC_DT_BLK(), zmm8);
                if (w_len > 9) _mm512_stream_ps(l_dst + 9 * OC_DT_BLK(), zmm9);
                if (w_len > 10) _mm512_stream_ps(l_dst + 10 * OC_DT_BLK(), zmm10);
                if (w_len > 11) _mm512_stream_ps(l_dst + 11 * OC_DT_BLK(), zmm11);
                if (w_len > 12) _mm512_stream_ps(l_dst + 12 * OC_DT_BLK(), zmm12);
                if (w_len > 13) _mm512_stream_ps(l_dst + 13 * OC_DT_BLK(), zmm13);
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                l_dst += dst_ocb_stride;
                if (w_len > 0) _mm512_stream_ps(l_dst + 0 * OC_DT_BLK(), zmm14);
                if (w_len > 1) _mm512_stream_ps(l_dst + 1 * OC_DT_BLK(), zmm15);
                if (w_len > 2) _mm512_stream_ps(l_dst + 2 * OC_DT_BLK(), zmm16);
                if (w_len > 3) _mm512_stream_ps(l_dst + 3 * OC_DT_BLK(), zmm17);
                if (w_len > 4) _mm512_stream_ps(l_dst + 4 * OC_DT_BLK(), zmm18);
                if (w_len > 5) _mm512_stream_ps(l_dst + 5 * OC_DT_BLK(), zmm19);
                if (w_len > 6) _mm512_stream_ps(l_dst + 6 * OC_DT_BLK(), zmm20);
                if (w_len > 7) _mm512_stream_ps(l_dst + 7 * OC_DT_BLK(), zmm21);
                if (w_len > 8) _mm512_stream_ps(l_dst + 8 * OC_DT_BLK(), zmm22);
                if (w_len > 9) _mm512_stream_ps(l_dst + 9 * OC_DT_BLK(), zmm23);
                if (w_len > 10) _mm512_stream_ps(l_dst + 10 * OC_DT_BLK(), zmm24);
                if (w_len > 11) _mm512_stream_ps(l_dst + 11 * OC_DT_BLK(), zmm25);
                if (w_len > 12) _mm512_stream_ps(l_dst + 12 * OC_DT_BLK(), zmm26);
                if (w_len > 13) _mm512_stream_ps(l_dst + 13 * OC_DT_BLK(), zmm27);
            }
        } else {
            float* l_dst = dst;
            const int64_t dst_ocb_stride = shar_param[DST_OCB_STRIDE_IDX()];
            if (oc_len > 0 * OC_DT_BLK()) {
                if (w_len > 0) _mm512_storeu_ps(l_dst + 0 * OC_DT_BLK(), zmm0);
                if (w_len > 1) _mm512_storeu_ps(l_dst + 1 * OC_DT_BLK(), zmm1);
                if (w_len > 2) _mm512_storeu_ps(l_dst + 2 * OC_DT_BLK(), zmm2);
                if (w_len > 3) _mm512_storeu_ps(l_dst + 3 * OC_DT_BLK(), zmm3);
                if (w_len > 4) _mm512_storeu_ps(l_dst + 4 * OC_DT_BLK(), zmm4);
                if (w_len > 5) _mm512_storeu_ps(l_dst + 5 * OC_DT_BLK(), zmm5);
                if (w_len > 6) _mm512_storeu_ps(l_dst + 6 * OC_DT_BLK(), zmm6);
                if (w_len > 7) _mm512_storeu_ps(l_dst + 7 * OC_DT_BLK(), zmm7);
                if (w_len > 8) _mm512_storeu_ps(l_dst + 8 * OC_DT_BLK(), zmm8);
                if (w_len > 9) _mm512_storeu_ps(l_dst + 9 * OC_DT_BLK(), zmm9);
                if (w_len > 10) _mm512_storeu_ps(l_dst + 10 * OC_DT_BLK(), zmm10);
                if (w_len > 11) _mm512_storeu_ps(l_dst + 11 * OC_DT_BLK(), zmm11);
                if (w_len > 12) _mm512_storeu_ps(l_dst + 12 * OC_DT_BLK(), zmm12);
                if (w_len > 13) _mm512_storeu_ps(l_dst + 13 * OC_DT_BLK(), zmm13);
            }
            if (oc_len > 1 * OC_DT_BLK()) {
                l_dst += dst_ocb_stride;
                if (w_len > 0) _mm512_storeu_ps(l_dst + 0 * OC_DT_BLK(), zmm14);
                if (w_len > 1) _mm512_storeu_ps(l_dst + 1 * OC_DT_BLK(), zmm15);
                if (w_len > 2) _mm512_storeu_ps(l_dst + 2 * OC_DT_BLK(), zmm16);
                if (w_len > 3) _mm512_storeu_ps(l_dst + 3 * OC_DT_BLK(), zmm17);
                if (w_len > 4) _mm512_storeu_ps(l_dst + 4 * OC_DT_BLK(), zmm18);
                if (w_len > 5) _mm512_storeu_ps(l_dst + 5 * OC_DT_BLK(), zmm19);
                if (w_len > 6) _mm512_storeu_ps(l_dst + 6 * OC_DT_BLK(), zmm20);
                if (w_len > 7) _mm512_storeu_ps(l_dst + 7 * OC_DT_BLK(), zmm21);
                if (w_len > 8) _mm512_storeu_ps(l_dst + 8 * OC_DT_BLK(), zmm22);
                if (w_len > 9) _mm512_storeu_ps(l_dst + 9 * OC_DT_BLK(), zmm23);
                if (w_len > 10) _mm512_storeu_ps(l_dst + 10 * OC_DT_BLK(), zmm24);
                if (w_len > 11) _mm512_storeu_ps(l_dst + 11 * OC_DT_BLK(), zmm25);
                if (w_len > 12) _mm512_storeu_ps(l_dst + 12 * OC_DT_BLK(), zmm26);
                if (w_len > 13) _mm512_storeu_ps(l_dst + 13 * OC_DT_BLK(), zmm27);
            }
        }
        src += w_len * stride_w;
        his += w_len * OC_DT_BLK();
        dst += w_len * OC_DT_BLK();
        ow -= w_len;
    } while (ow > 0);
#undef KW_COMPUTE_STEP
}

}}};

#endif
