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

#include "ppl/kernel/riscv/common/internal_include.h"
#include "ppl/kernel/riscv/common/where/where_common.h"

namespace ppl { namespace kernel { namespace riscv {

ppl::common::RetCode where_eltwise_fp16(
    const ppl::common::TensorShape *dst_shape,
    const uint8_t *cond,
    const __fp16 *src_x,
    const __fp16 *src_y,
    __fp16 *dst)
{
    return where_eltwise_common<__fp16>(
        dst_shape,
        cond,
        src_x,
        src_y,
        dst);
}

ppl::common::RetCode where_ndarray_fp16(
    const ppl::common::TensorShape *cond_shape,
    const ppl::common::TensorShape *src_x_shape,
    const ppl::common::TensorShape *src_y_shape,
    const ppl::common::TensorShape *dst_shape,
    const uint8_t *cond,
    const __fp16 *src_x,
    const __fp16 *src_y,
    __fp16 *dst)
{
    return where_ndarray_common<__fp16>(
        cond_shape,
        src_x_shape,
        src_y_shape,
        dst_shape,
        cond,
        src_x,
        src_y,
        dst);
}

}}} // namespace ppl::kernel::riscv