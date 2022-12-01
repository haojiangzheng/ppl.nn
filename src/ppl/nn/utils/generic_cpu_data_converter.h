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

#ifndef _ST_HPC_PPL_NN_UTILS_GENERIC_CPU_DATA_CONVERTER_H_
#define _ST_HPC_PPL_NN_UTILS_GENERIC_CPU_DATA_CONVERTER_H_

#include "ppl/nn/common/data_converter.h"

namespace ppl { namespace nn { namespace utils {

class GenericCpuDataConverter final : public DataConverter {
public:
    ppl::common::RetCode ConvertToHost(void* dst, const ppl::common::TensorShape& dst_desc, const BufferDesc& src,
                                       const ppl::common::TensorShape& src_desc,
                                       const void* src_custom_info = nullptr) const override;

    ppl::common::RetCode ConvertFromHost(BufferDesc* dst, const ppl::common::TensorShape& dst_desc, const void* src,
                                         const ppl::common::TensorShape& src_desc,
                                         const void* dst_custom_info = nullptr) const override;

    ppl::common::RetCode Convert(BufferDesc* dst, const ppl::common::TensorShape& dst_desc, const BufferDesc& src,
                                 const ppl::common::TensorShape& src_desc, const void* dst_custom_info = nullptr,
                                 const void* src_custom_info = nullptr) const override;
};

}}} // namespace ppl::nn::utils

#endif
