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

#ifndef __ST_PPL_KERNEL_RISCV_INT64_ARITHMETIC_ARITHMETIC_BROADCAST_N2CX_INT64_H_
#define __ST_PPL_KERNEL_RISCV_INT64_ARITHMETIC_ARITHMETIC_BROADCAST_N2CX_INT64_H_

#include "ppl/nn/runtime/tensor_impl.h"
#include "arithmetic_kernel_int64.h"

namespace ppl { namespace kernel { namespace riscv {

#define C_BLK() ((int64_t)2)

template <arithmetic_op_type_t op, bool fuse_relu>
static inline void arithmetic_broadcast_lastdim_no_broadcast_n2cx_int64(const int64_t* src0, const int64_t* src1, int64_t* dst,

                                                                        const int64_t start,
                                                                        const int64_t end,
                                                                        const bool c0_broadcast,
                                                                        const bool c1_broadcast)
{
    const int64_t parall_d   = 16;
    const int64_t unroll_len = parall_d * C_BLK();
    const auto vl            = vsetvli(C_BLK(), RVV_E64, RVV_M1);

    int64_t i = start;
    if (!c0_broadcast && !c1_broadcast) {
        for (; i + unroll_len < end * C_BLK(); i += unroll_len) { // end ?
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata0, vdata1, vdata2, vdata3;
            int64xm1_t vdata4, vdata5, vdata6, vdata7;
            int64xm1_t vdata8, vdata9, vdata10, vdata11;
            int64xm1_t vdata12, vdata13, vdata14, vdata15;

            vdata0  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 0 * C_BLK(), vl));
            vdata1  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 1 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 1 * C_BLK(), vl));
            vdata2  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 2 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 2 * C_BLK(), vl));
            vdata3  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 3 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 3 * C_BLK(), vl));
            vdata4  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 4 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 4 * C_BLK(), vl));
            vdata5  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 5 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 5 * C_BLK(), vl));
            vdata6  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 6 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 6 * C_BLK(), vl));
            vdata7  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 7 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 7 * C_BLK(), vl));
            vdata8  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 8 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 8 * C_BLK(), vl));
            vdata9  = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 9 * C_BLK(), vl),
                                                        vlev_int64xm1(src1_ + 9 * C_BLK(), vl));
            vdata10 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 10 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 10 * C_BLK(), vl));
            vdata11 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 11 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 11 * C_BLK(), vl));
            vdata12 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 12 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 12 * C_BLK(), vl));
            vdata13 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 13 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 13 * C_BLK(), vl));
            vdata14 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 14 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 14 * C_BLK(), vl));
            vdata15 = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 15 * C_BLK(), vl),
                                                         vlev_int64xm1(src1_ + 15 * C_BLK(), vl));

            if (fuse_relu) {
                vsev_int64xm1(dst_ + 0 * C_BLK(), vmaxvx_int64xm1(vdata0, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 1 * C_BLK(), vmaxvx_int64xm1(vdata1, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vmaxvx_int64xm1(vdata2, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vmaxvx_int64xm1(vdata3, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vmaxvx_int64xm1(vdata4, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vmaxvx_int64xm1(vdata5, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vmaxvx_int64xm1(vdata6, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vmaxvx_int64xm1(vdata7, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vmaxvx_int64xm1(vdata8, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vmaxvx_int64xm1(vdata9, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vmaxvx_int64xm1(vdata10, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vmaxvx_int64xm1(vdata11, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vmaxvx_int64xm1(vdata12, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vmaxvx_int64xm1(vdata13, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vmaxvx_int64xm1(vdata14, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vmaxvx_int64xm1(vdata15, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_ + 0 * C_BLK(), vdata0, vl);
                vsev_int64xm1(dst_ + 1 * C_BLK(), vdata1, vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vdata2, vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vdata3, vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vdata4, vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vdata5, vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vdata6, vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vdata7, vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vdata8, vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vdata9, vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vdata10, vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vdata11, vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vdata12, vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vdata13, vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vdata14, vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vdata15, vl);
            }
        }
        for (; i < end * C_BLK(); i += C_BLK()) {
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata;
            vdata = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_, vl), vlev_int64xm1(src1_, vl));
            if (fuse_relu) {
                vsev_int64xm1(dst_, vmaxvx_int64xm1(vdata, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_, vdata, vl);
            }
        }
    } else if (c0_broadcast) {
        for (; i + unroll_len < end * C_BLK(); i += unroll_len) { //  end ?
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata0, vdata1, vdata2, vdata3;
            int64xm1_t vdata4, vdata5, vdata6, vdata7;
            int64xm1_t vdata8, vdata9, vdata10, vdata11;
            int64xm1_t vdata12, vdata13, vdata14, vdata15;

            int64xm1_t vsrc0 = vmvvx_int64xm1(*src0_, vl);
            vdata0           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 0 * C_BLK(), vl));
            vdata1           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 1 * C_BLK(), vl));
            vdata2           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 2 * C_BLK(), vl));
            vdata3           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 3 * C_BLK(), vl));
            vdata4           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 4 * C_BLK(), vl));
            vdata5           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 5 * C_BLK(), vl));
            vdata6           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 6 * C_BLK(), vl));
            vdata7           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 7 * C_BLK(), vl));
            vdata8           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 8 * C_BLK(), vl));
            vdata9           = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 9 * C_BLK(), vl));
            vdata10          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 10 * C_BLK(), vl));
            vdata11          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 11 * C_BLK(), vl));
            vdata12          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 12 * C_BLK(), vl));
            vdata13          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 13 * C_BLK(), vl));
            vdata14          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 14 * C_BLK(), vl));
            vdata15          = arithmetic_vector_kernel_int64<op>(vsrc0, vlev_int64xm1(src1_ + 15 * C_BLK(), vl));

            if (fuse_relu) {
                vsev_int64xm1(dst_ + 1 * C_BLK(), vmaxvx_int64xm1(vdata1, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vmaxvx_int64xm1(vdata2, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vmaxvx_int64xm1(vdata3, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vmaxvx_int64xm1(vdata4, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vmaxvx_int64xm1(vdata5, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vmaxvx_int64xm1(vdata6, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vmaxvx_int64xm1(vdata7, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vmaxvx_int64xm1(vdata8, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vmaxvx_int64xm1(vdata9, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vmaxvx_int64xm1(vdata10, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vmaxvx_int64xm1(vdata11, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vmaxvx_int64xm1(vdata12, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vmaxvx_int64xm1(vdata13, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vmaxvx_int64xm1(vdata14, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vmaxvx_int64xm1(vdata15, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_ + 0 * C_BLK(), vdata0, vl);
                vsev_int64xm1(dst_ + 1 * C_BLK(), vdata1, vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vdata2, vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vdata3, vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vdata4, vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vdata5, vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vdata6, vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vdata7, vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vdata8, vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vdata9, vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vdata10, vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vdata11, vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vdata12, vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vdata13, vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vdata14, vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vdata15, vl);
            }
        }
        for (; i + C_BLK() < end * C_BLK(); i += C_BLK()) {
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata;
            vdata =
                arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_, vl), vlev_int64xm1(src1_, vl)); //  broadcast ?
            if (fuse_relu) {
                vsev_int64xm1(dst_, vmaxvx_int64xm1(vdata, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_, vdata, vl);
            }
        }
    } else if (c1_broadcast) {
        for (; i + unroll_len < end * C_BLK(); i += unroll_len) {
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata0, vdata1, vdata2, vdata3;
            int64xm1_t vdata4, vdata5, vdata6, vdata7;
            int64xm1_t vdata8, vdata9, vdata10, vdata11;
            int64xm1_t vdata12, vdata13, vdata14, vdata15;

            int64xm1_t vsrc1 = vmvvx_int64xm1(*src1_, vl);
            vdata0           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata1           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata2           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata3           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata4           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata5           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata6           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata7           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata8           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata9           = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata10          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata11          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata12          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata13          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata14          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);
            vdata15          = arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_ + 0 * C_BLK(), vl), vsrc1);

            if (fuse_relu) {
                vsev_int64xm1(dst_ + 1 * C_BLK(), vmaxvx_int64xm1(vdata1, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vmaxvx_int64xm1(vdata2, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vmaxvx_int64xm1(vdata3, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vmaxvx_int64xm1(vdata4, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vmaxvx_int64xm1(vdata5, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vmaxvx_int64xm1(vdata6, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vmaxvx_int64xm1(vdata7, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vmaxvx_int64xm1(vdata8, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vmaxvx_int64xm1(vdata9, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vmaxvx_int64xm1(vdata10, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vmaxvx_int64xm1(vdata11, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vmaxvx_int64xm1(vdata12, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vmaxvx_int64xm1(vdata13, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vmaxvx_int64xm1(vdata14, (int64_t)0, vl), vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vmaxvx_int64xm1(vdata15, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_ + 0 * C_BLK(), vdata0, vl);
                vsev_int64xm1(dst_ + 1 * C_BLK(), vdata1, vl);
                vsev_int64xm1(dst_ + 2 * C_BLK(), vdata2, vl);
                vsev_int64xm1(dst_ + 3 * C_BLK(), vdata3, vl);
                vsev_int64xm1(dst_ + 4 * C_BLK(), vdata4, vl);
                vsev_int64xm1(dst_ + 5 * C_BLK(), vdata5, vl);
                vsev_int64xm1(dst_ + 6 * C_BLK(), vdata6, vl);
                vsev_int64xm1(dst_ + 7 * C_BLK(), vdata7, vl);
                vsev_int64xm1(dst_ + 8 * C_BLK(), vdata8, vl);
                vsev_int64xm1(dst_ + 9 * C_BLK(), vdata9, vl);
                vsev_int64xm1(dst_ + 10 * C_BLK(), vdata10, vl);
                vsev_int64xm1(dst_ + 11 * C_BLK(), vdata11, vl);
                vsev_int64xm1(dst_ + 12 * C_BLK(), vdata12, vl);
                vsev_int64xm1(dst_ + 13 * C_BLK(), vdata13, vl);
                vsev_int64xm1(dst_ + 14 * C_BLK(), vdata14, vl);
                vsev_int64xm1(dst_ + 15 * C_BLK(), vdata15, vl);
            }
        }
        for (; i + C_BLK() < end * C_BLK(); i += C_BLK()) {
            const int64_t* src0_ = src0 + i;
            const int64_t* src1_ = src1 + i;
            int64_t* dst_        = dst + i;

            int64xm1_t vdata;
            vdata =
                arithmetic_vector_kernel_int64<op>(vlev_int64xm1(src0_, vl), vlev_int64xm1(src1_, vl)); //  broadcast ?
            if (fuse_relu) {
                vsev_int64xm1(dst_, vmaxvx_int64xm1(vdata, (int64_t)0, vl), vl);
            } else {
                vsev_int64xm1(dst_, vdata, vl);
            }
        }
    }
}

template <arithmetic_op_type_t op, bool fuse_relu>
static inline void arithmetic_broadcast_lastdim_src0_broadcast_n2cx_int64(const int64_t* src0, const int64_t* src1, int64_t* dst,

                                                                          const int64_t start,
                                                                          const int64_t end,
                                                                          const bool c0_broadcast,
                                                                          const bool c1_broadcast)
{
    // const int64_t parall_d = 16;
    // const int64_t unroll_len = parall_d * C_BLK();
    const auto vl = vsetvli(C_BLK(), RVV_E64, RVV_M1);

    int64xm1_t vbroadcast_src0;
    if (!c0_broadcast) {
        vbroadcast_src0 = vlev_int64xm1(src0, vl);
    } else {
        vbroadcast_src0 = vmvvx_int64xm1(*src0, vl);
    }

    int64_t i = start;
    if (!c1_broadcast) {
        for (; i <= end; i++) {
            int64xm1_t vsrc1 = vlev_int64xm1(src1 + i * C_BLK(), vl);
            int64xm1_t vdst  = arithmetic_vector_kernel_int64<op>(vbroadcast_src0, vsrc1);
            if (fuse_relu) {
                vdst = vmaxvx_int64xm1(vdst, (int64_t)0, vl);
            }
            vsev_int64xm1(dst + i * C_BLK(), vdst, vl);
        }
    } else {
        for (; i <= end; i++) {
            int64xm1_t vsrc1 = vmvvx_int64xm1(*(src1 + i * C_BLK()), vl);
            int64xm1_t vdst  = arithmetic_vector_kernel_int64<op>(vbroadcast_src0, vsrc1);
            if (fuse_relu) {
                vdst = vmaxvx_int64xm1(vdst, (int64_t)0, vl);
            }
            vsev_int64xm1(dst + i * C_BLK(), vdst, vl);
        }
    }
}

template <arithmetic_op_type_t op, bool fuse_relu>
static inline void arithmetic_broadcast_lastdim_src1_broadcast_n2cx_int64(const int64_t* src0, const int64_t* src1, int64_t* dst,

                                                                          const int64_t start,
                                                                          const int64_t end,
                                                                          const bool c0_broadcast,
                                                                          const bool c1_broadcast)
{
    const auto vl = vsetvli(C_BLK(), RVV_E64, RVV_M1);

    int64xm1_t vbroadcast_src1;
    if (!c1_broadcast) {
        vbroadcast_src1 = vlev_int64xm1(src1, vl);
    } else {
        vbroadcast_src1 = vmvvx_int64xm1(*src1, vl);
    }

    int64_t i = start;
    if (!c0_broadcast) {
        for (; i <= end; i++) {
            int64xm1_t vsrc0 = vlev_int64xm1(src0 + i * C_BLK(), vl);
            int64xm1_t vdst  = arithmetic_vector_kernel_int64<op>(vsrc0, vbroadcast_src1);
            if (fuse_relu) {
                vdst = vmaxvx_int64xm1(vdst, (int64_t)0, vl);
            }
            vsev_int64xm1(dst + i * C_BLK(), vdst, vl);
        }
    } else {
        for (; i <= end; i++) {
            int64xm1_t vsrc0 = vmvvx_int64xm1(*(src0 + i * C_BLK()), vl);
            int64xm1_t vdst  = arithmetic_vector_kernel_int64<op>(vsrc0, vbroadcast_src1);
            if (fuse_relu) {
                vdst = vmaxvx_int64xm1(vdst, (int64_t)0, vl);
            }
            vsev_int64xm1(dst + i * C_BLK(), vdst, vl);
        }
    }
}

template <arithmetic_op_type_t op, bool fuse_relu>
static ppl::common::RetCode arithmetic_broadcast_recursive_n2cx_int64(
    const int64_t* src0,
    const int64_t* src1,
    int64_t* dst,

    const int64_t* src0_shape,
    const int64_t* src1_shape,
    const int64_t* dst_shape,
    const int64_t* inc0,
    const int64_t* inc1,
    const int64_t* inc_out,
    const int64_t dim_count,
    const int64_t dim_idx,
    const int64_t c0_broadcast,
    const int64_t c1_broadcast,
    parallel_block* block)
{
    bool is_first       = is_first_dim(block, dim_idx);
    bool is_last        = is_last_dim(block, dim_idx);
    const int64_t start = is_first ? block->start[dim_idx] : 0;
    const int64_t end   = is_last ? block->end[dim_idx] : dst_shape[dim_idx] - 1;

    if (dim_idx == dim_count - 1) {
        if (src0_shape[dim_idx] == src1_shape[dim_idx]) {
            arithmetic_broadcast_lastdim_no_broadcast_n2cx_int64<op, fuse_relu>(src0, src1, dst, start, end, c0_broadcast, c1_broadcast);
        } else if (src0_shape[dim_idx] == 1) {
            arithmetic_broadcast_lastdim_src0_broadcast_n2cx_int64<op, fuse_relu>(src0, src1, dst, start, end, c0_broadcast, c1_broadcast);
        } else if (src1_shape[dim_idx] == 1) {
            arithmetic_broadcast_lastdim_src1_broadcast_n2cx_int64<op, fuse_relu>(src0, src1, dst, start, end, c0_broadcast, c1_broadcast);
        }
    } else {
        for (block->idx[dim_idx] = start; block->idx[dim_idx] <= end; block->idx[dim_idx]++) {
            int64_t i = block->idx[dim_idx];
            arithmetic_broadcast_recursive_n2cx_int64<op, fuse_relu>(
                src0 + i * inc0[dim_idx], src1 + i * inc1[dim_idx], dst + i * inc_out[dim_idx],

                src0_shape,
                src1_shape,
                dst_shape,
                inc0,
                inc1,
                inc_out,
                dim_count,
                dim_idx + 1,
                c0_broadcast,
                c1_broadcast,
                block);
        }
    }

    return ppl::common::RC_SUCCESS;
}

template <arithmetic_op_type_t op, bool fuse_relu>
static ppl::common::RetCode arithmetic_broadcast_n2cx_int64(const int64_t* src0, const int64_t* src1, int64_t* dst,

                                                            const ppl::common::TensorShape* src0_shape,
                                                            const ppl::common::TensorShape* src1_shape,
                                                            const ppl::common::TensorShape* dst_shape,
                                                            const int64_t c_dim_dix)
{
    // pad 1 to input's high dims
    const int64_t dim_count = dst_shape->GetDimCount();
    if (dim_count > PPL_RISCV_TENSOR_MAX_DIMS()) {
        return ppl::common::RC_UNSUPPORTED;
    }

    int64_t padded_src0_shape[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    int64_t padded_src1_shape[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    pad_shape(src0_shape, dim_count, padded_src0_shape);
    pad_shape(src1_shape, dim_count, padded_src1_shape);
    const bool c0_broadcast =
        padded_src0_shape[c_dim_dix] != padded_src1_shape[c_dim_dix] && padded_src0_shape[c_dim_dix] == 1;
    const bool c1_broadcast =
        padded_src0_shape[c_dim_dix] != padded_src1_shape[c_dim_dix] && padded_src1_shape[c_dim_dix] == 1;

    // compress dims
    int64_t real_dim_count                               = 0;
    int64_t real_c_dim_idx                               = c_dim_dix;
    int64_t real_src0_shape[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    int64_t real_src1_shape[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};
    int64_t real_dst_shape[PPL_RISCV_TENSOR_MAX_DIMS()]  = {0};

    // remove 1 on high dims to compress dim count
    // stop at C dim
    for (int64_t i = 0; i < dim_count; i++) {
        if (dst_shape->GetDim(i) <= 1 && i < c_dim_dix) {
            real_c_dim_idx--;
        }
        real_src0_shape[real_dim_count] = padded_src0_shape[i];
        real_src1_shape[real_dim_count] = padded_src1_shape[i];
        real_dst_shape[real_dim_count]  = dst_shape->GetDim(i);
        real_dim_count++;
    }

    // merge low dims
    // stop at C dim
    for (int64_t i = real_dim_count - 1; i >= real_c_dim_idx + 2; i--) {
        bool cur_dim_input0_need_broadcast = real_src0_shape[i] != real_src1_shape[i] && real_src0_shape[i] == 1;
        bool cur_dim_input1_need_broadcast = real_src0_shape[i] != real_src1_shape[i] && real_src1_shape[i] == 1;
        bool prev_dim_input0_need_broadcast =
            real_src0_shape[i - 1] != real_src1_shape[i - 1] && real_src0_shape[i - 1] == 1;
        bool prev_dim_input1_need_broadcast =
            real_src0_shape[i - 1] != real_src1_shape[i - 1] && real_src1_shape[i - 1] == 1;

        if (cur_dim_input0_need_broadcast == prev_dim_input0_need_broadcast && // can merge
            cur_dim_input1_need_broadcast == prev_dim_input1_need_broadcast) {
            real_src0_shape[i - 1] *= real_src0_shape[i];
            real_src1_shape[i - 1] *= real_src1_shape[i];
            real_dst_shape[i - 1] *= real_dst_shape[i];
            real_dim_count--;
        } else {
            break;
        }
    }

    int64_t inc0[PPL_RISCV_TENSOR_MAX_DIMS()]    = {0};
    int64_t inc1[PPL_RISCV_TENSOR_MAX_DIMS()]    = {0};
    int64_t inc_out[PPL_RISCV_TENSOR_MAX_DIMS()] = {0};

    // div C dim by C_BLK() and set stride_w to C_BLK();
    int64_t stride0                 = C_BLK();
    int64_t stride1                 = C_BLK();
    int64_t stride_out              = C_BLK();
    real_src0_shape[real_c_dim_idx] = div_up(real_src0_shape[real_c_dim_idx], C_BLK());
    real_src1_shape[real_c_dim_idx] = div_up(real_src1_shape[real_c_dim_idx], C_BLK());
    real_dst_shape[real_c_dim_idx]  = div_up(real_dst_shape[real_c_dim_idx], C_BLK());

    // prepare incs
    for (int64_t i = real_dim_count - 1; i >= 0; i--) {
        inc0[i]    = real_src0_shape[i] == 1 ? 0 : stride0;
        inc1[i]    = real_src1_shape[i] == 1 ? 0 : stride1;
        inc_out[i] = stride_out;

        stride0 *= real_src0_shape[i];
        stride1 *= real_src1_shape[i];
        stride_out *= real_dst_shape[i];
    }

    const int64_t total_len = dst_shape->CalcElementsIncludingPadding() / C_BLK();
    parallel_block block;
    {
        int64_t start_idx = 0;
        int64_t end_idx   = total_len - 1;
        idx2dims(start_idx, real_dst_shape, real_dim_count, block.start);
        idx2dims(end_idx, real_dst_shape, real_dim_count, block.end);
        block.id = 0;
        for (int64_t i = 0; i < real_dim_count; i++) {
            block.idx[i] = block.start[i];
        }
    }

    arithmetic_broadcast_recursive_n2cx_int64<op, fuse_relu>(src0, src1, dst,

                                                             real_src0_shape,
                                                             real_src1_shape,
                                                             real_dst_shape,
                                                             inc0,
                                                             inc1,
                                                             inc_out,
                                                             real_dim_count,
                                                             0,
                                                             c0_broadcast,
                                                             c1_broadcast,
                                                             &block);

    return ppl::common::RC_SUCCESS;
}

}}}; // namespace ppl::kernel::riscv

#endif //  __ST_PPL_KERNEL_RISCV_INT64_ARITHMETIC_ARITHMETIC_BROADCAST_N2CX_INT64_H_
