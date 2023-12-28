#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

// #include "logger/logger.h"
#include "memory/memory_distributor.h"

namespace
{
constexpr int32_t one_gigabyte = 1024 * 1024 * 1024;

// File static + exceptions disabled, no linting necessary here
// We reserve 4 gigs of memory for our game
deep::memory::MemoryDistributor memory_distributor{ one_gigabyte };// NOLINT

using AllocatorType = deep::memory::MemoryDistributor::AllocatorType;
}// namespace

// TODO: Figure out the logging situation in release mode for these overrides

void *operator new(std::size_t size)
{
    memory_distributor.UpdateHeapStats(
      { .total_allocated = size, .total_deallocated = 0, .current_allocated = size, .unsized_allocations = 0 });

    auto *ptr = malloc(size);
    if (ptr == nullptr)
    {
        // deep::Logger::assert_and_log(fmt::format("Failed to allocate {} bytes of memory", size), false);
    }

    return ptr;
}

void operator delete(void *ptr, std::size_t size)
{
    memory_distributor.UpdateHeapStats({.total_allocated = 0, .total_deallocated = size, .current_allocated = 0, .unsized_allocations = 0});
    std::free(ptr);// NOLINT
}

void *operator new[](std::size_t size)
{
    memory_distributor.UpdateHeapStats({.total_allocated = size, .total_deallocated = 0, .current_allocated = size, .unsized_allocations = 0});

    auto *ptr = malloc(size);
    if (ptr == nullptr)
    {
        // deep::Logger::assert_and_log(fmt::format("Failed to allocate {} bytes of memory", size), false);
    }

    return ptr;
}

void operator delete[](void *ptr, std::size_t size)
{
    memory_distributor.UpdateHeapStats({.total_allocated = 0, .total_deallocated = size, .current_allocated = 0, .unsized_allocations = 0});
    std::free(ptr);
}

void operator delete(void *ptr) noexcept
{
    memory_distributor.UpdateHeapStats({ .total_allocated = 0, .total_deallocated = 0, .current_allocated = 0, .unsized_allocations = 1 });
    std::free(ptr);
}

void operator delete[](void *ptr) noexcept
{
    memory_distributor.UpdateHeapStats({ .total_allocated = 0, .total_deallocated = 0, .current_allocated = 0, .unsized_allocations = 1 });
    std::free(ptr);
}

void *operator new(std::size_t size, AllocatorType allocator_type)
{
    memory_distributor.UpdateHeapStats({.total_allocated = size, .total_deallocated = 0, .current_allocated = 0, .unsized_allocations = 0});

    auto &alloc = ::memory_distributor.GetAllocatorByEnum(allocator_type);

    return alloc.allocate(size).data();
}

void operator delete(void *ptr, std::size_t size, AllocatorType allocator_type)
{
    memory_distributor.UpdateHeapStats({.total_allocated = 0, .total_deallocated = size, .current_allocated = 0, .unsized_allocations = 0});

    auto &alloc = ::memory_distributor.GetAllocatorByEnum(allocator_type);

    alloc.deallocate(std::span<std::byte>(reinterpret_cast<std::byte *>(ptr), size));
}
