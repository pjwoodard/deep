#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "logger/logger.h"
#include "memory/memory_distributor.h"

namespace
{
constexpr int32_t one_gigabyte = 1024 * 1024 * 1024;

// File static + exceptions disabled, no linting necessary here
// We reserve 4 gigs of memory for our game
deep::memory::MemoryDistributor memory_distributor{ one_gigabyte };// NOLINT

using AllocatorType = deep::memory::MemoryDistributor::AllocatorType;
}// namespace

void *operator new(std::size_t size)
{
    memory_distributor.UpdateHeapStats(size, 0);

    auto *ptr = malloc(size);
    if (ptr == nullptr)
    {
        deep::Logger::assert_and_log(fmt::format("Failed to allocate {} bytes of memory", size), false);
    }

    return ptr;
}

void operator delete(void *ptr, std::size_t size)
{
    memory_distributor.UpdateHeapStats(0, size);
    free(ptr);// NOLINT
}

void *operator new[](std::size_t size)
{
    memory_distributor.UpdateHeapStats(size, 0);

    auto *ptr = malloc(size);
    if (ptr == nullptr)
    {
        deep::Logger::assert_and_log(fmt::format("Failed to allocate {} bytes of memory", size), false);
    }

    return ptr;
}

void operator delete[](void *ptr, std::size_t size)
{
    memory_distributor.UpdateHeapStats(0, size);
    free(ptr);
}

void operator delete(void* ptr) noexcept
{
    deep::Logger::warn_core("Unsized raw delete called");
    free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    deep::Logger::warn_core("Unsized raw delete[] called");
    free(ptr);
}

void *operator new(std::size_t size, AllocatorType allocator_type)
{
    auto &alloc = ::memory_distributor.GetAllocatorByEnum(allocator_type);

    return alloc.allocate(size).data();
}

void operator delete(void *ptr, std::size_t size, AllocatorType allocator_type)
{
    deep::Logger::assert_and_log(fmt::format("Deleting memory from allocator type {}", allocator_type), ptr != nullptr);

    auto &alloc = ::memory_distributor.GetAllocatorByEnum(allocator_type);

    alloc.deallocate(std::span<std::byte>(reinterpret_cast<std::byte *>(ptr), size));
}
