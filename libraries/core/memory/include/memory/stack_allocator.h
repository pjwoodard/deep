#pragma once

#include <cstddef>
#include <new>
#include <span>

#include "logger/logger.h"

namespace deep::memory
{
class StackAllocator {
public:
    std::span<std::byte> allocate(size_t size)
    {
        if(stack_marker_ + size > pool_size_)
        {
            deep::Logger::assert_and_log(fmt::format("StackAllocator ran out of memory. Requested {} bytes, but only {} bytes are available", size, pool_size_ - stack_marker_), false);
        }

        const auto& memory = std::span<std::byte>(pool_ + stack_marker_, size);

        prev_stack_marker_ = stack_marker_;
        stack_marker_ += size;

        return memory;
    };

    void deallocate(std::span<std::byte> /*memory*/)
    {
        stack_marker_ = prev_stack_marker_;
    };

    // We can probably manage our portion of the pool with a unique pointer rather than having a destructor here
    StackAllocator(std::byte *pool, size_t size) noexcept : pool_(pool), pool_size_(size) {}
    ~StackAllocator() { delete[] pool_; }

    // No default construction allowed, must provide a size
    StackAllocator() noexcept = delete;
    StackAllocator(StackAllocator&&) noexcept = delete;
    StackAllocator(const StackAllocator&) noexcept = delete;

private:
    size_t stack_marker_{0}; // Pointer to the top of the stack
    size_t prev_stack_marker_{0}; // Pointer to the top of the last element 
    std::byte* pool_{nullptr}; 
    size_t pool_size_{0};
};
}