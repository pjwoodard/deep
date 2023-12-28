#pragma once

#include <cstddef>
#include <magic_enum/magic_enum.hpp>

#include "logger/logger.h"
#include "memory/stack_allocator.h"

namespace deep::memory
{
// \brief MemoryDistributor is a class that manages the memory of the engine.
// \note This class should be the only place this engine requests memory from the OS.
//       The rest of the calls to new/delete should be handled by the MemoryDistributor.
class MemoryDistributor
{
  public:
    // Constructor with a size and a destructor.
    MemoryDistributor(std::size_t size)
      : raw_memory_block_{ std::make_unique<std::byte[]>(size) }
      , total_memory_size_{ size }
      , stack_allocator_{ raw_memory_block_.get(), total_memory_size_ } {};

    // Every other operation on this class is deleted, no copies or moves allowed.
    MemoryDistributor() = delete;
    MemoryDistributor(const MemoryDistributor &) = delete;
    MemoryDistributor &operator=(const MemoryDistributor &) = delete;
    MemoryDistributor(MemoryDistributor &&) = delete;
    MemoryDistributor &operator=(MemoryDistributor &&) = delete;

    enum class AllocatorType
    {
        StackAllocator
    };

    struct HeapStats
    {
        size_t total_allocated;
        size_t total_deallocated;
        size_t current_allocated;
        size_t unsized_allocations;
    };

    static HeapStats GetHeapStats() { return heap_stats_; };

    void UpdateHeapStats(const HeapStats& heap_stats)
    {
        heap_stats_.total_allocated += heap_stats.total_allocated;
        heap_stats_.total_deallocated += heap_stats.total_deallocated;
        heap_stats_.unsized_allocations += heap_stats.unsized_allocations;

        heap_stats_.current_allocated = heap_stats_.total_allocated - heap_stats_.total_deallocated;
    };

    auto &GetAllocatorByEnum(AllocatorType alloc_type)
    {
        switch (alloc_type)
        {
        case AllocatorType::StackAllocator:
            return stack_allocator_;
        default:
            deep::Logger::assert_and_log(fmt::format("Invalid allocator type {}", magic_enum::enum_name(alloc_type)), false);
            // We assert in debug builds and return a stack allocator in release builds.
            return stack_allocator_;
        }
    };

  private:
    std::unique_ptr<std::byte[]> raw_memory_block_;
    size_t total_memory_size_;
    StackAllocator stack_allocator_;
    inline static HeapStats heap_stats_;
};
}// namespace deep::memory
