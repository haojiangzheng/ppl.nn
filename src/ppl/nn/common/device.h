#ifndef _ST_HPC_PPL_NN_COMMON_DEVICE_H_
#define _ST_HPC_PPL_NN_COMMON_DEVICE_H_

#include "ppl/common/retcode.h"
#include "ppl/common/allocator.h"
#include "ppl/nn/common/tensor_shape.h"
#include "ppl/nn/common/buffer_desc.h"
#include "ppl/nn/common/data_converter.h"
#include "ppl/nn/common/types.h"
#include "ppl/nn/runtime/barrier.h"

namespace ppl { namespace nn {

class Device {
public:
    virtual ~Device() {}

    /**
       @brief reallocate `buffer` with new size `bytes`.
       @param bytes new buffer size needed
       @param buffer the result
       @note previous memory in `buffer` would be freed.
    */
    virtual ppl::common::RetCode Realloc(uint64_t bytes, BufferDesc* buffer) = 0;

    /**
       @brief reallocate `buffer` with new shape `shape`.
       @param shape the buffer shape needed
       @param buffer the result
       @note previous memory in `buffer` would be freed.
    */
    virtual ppl::common::RetCode Realloc(const TensorShape& shape, BufferDesc* buffer) = 0;

    /** @brief free `buffer` allocated by Realloc() */
    virtual void Free(BufferDesc* buffer) = 0;

    /**
       @brief copy `bytes` bytes from `src` to `dst`
       @param dst pointer to data area on this device
       @param src pointer to cpu memory
    */
    virtual ppl::common::RetCode CopyFromHost(BufferDesc* dst, const void* src, uint64_t bytes) const = 0;

    /**
       @brief copy data described by `shape` from `src` to `dst`
       @param dst points to data area on this device
       @param src points to cpu memory
    */
    virtual ppl::common::RetCode CopyFromHost(BufferDesc* dst, const void* src, const TensorShape& shape) const = 0;

    /**
       @brief copy `bytes` bytes from `src` to `dst`
       @param dst points to cpu memory
       @param src points to data area on this device
    */
    virtual ppl::common::RetCode CopyToHost(void* dst, const BufferDesc& src, uint64_t bytes) const = 0;

    /**
       @brief copy data described by `shape` from `src` to `dst`
       @param dst points to cpu memory
       @param src points to data area on this device
    */
    virtual ppl::common::RetCode CopyToHost(void* dst, const BufferDesc& src, const TensorShape& shape) const = 0;

    /**
       @brief copy `bytes` bytes from `src` to `dst`
       @param dst points to data area on this device
       @param src points to data area on this device
    */
    virtual ppl::common::RetCode Copy(BufferDesc* dst, const BufferDesc& src, uint64_t bytes) const = 0;

    /**
       @brief copy data described by `shape` from `src` to `dst`
       @param dst points to data area on this device
       @param src points to data area on this device
    */
    virtual ppl::common::RetCode Copy(BufferDesc* dst, const BufferDesc& src, const TensorShape& shape) const = 0;

    /** @brief create a barrier that is used for synchronization between different devices. */
    virtual std::shared_ptr<Barrier> CreateBarrier() {
        return std::shared_ptr<Barrier>();
    }

    /** @brief get DataConverter that can process data on this device */
    virtual const DataConverter* GetDataConverter() const = 0;
};

}} // namespace ppl::nn

#endif
