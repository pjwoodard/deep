#include <catch2/catch_test_macros.hpp>

#include "memory/stack_allocator.h"

TEST_CASE("Stack allocator works", "[stack_allocator]")
{
    std::unique_ptr<std::byte[]> pool(new std::byte[1024]);
    deep::memory::StackAllocator stack_allocator(pool.get(), 1024);
    auto bytes_view = stack_allocator.allocate(512);
    REQUIRE(bytes_view.size() == 512);

    auto bytes_view2 = stack_allocator.allocate(256);
    REQUIRE(bytes_view2.size() == 256);
}

// TEST_CASE("Stack allocator works with alignment", "[stack_allocator]")
// {
//     StackAllocator stack_allocator(1024);
//     auto* ptr = stack_allocator.Allocate(512, 16);
//     REQUIRE(ptr != nullptr);
//     REQUIRE(stack_allocator.GetUsedMemory() == 512);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 1);
//     stack_allocator.Free(ptr);
//     REQUIRE(stack_allocator.GetUsedMemory() == 0);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 0);
// }

// TEST_CASE("Stack allocator works with multiple allocations", "[stack_allocator]")
// {
//     StackAllocator stack_allocator(1024);
//     auto* ptr1 = stack_allocator.Allocate(512);
//     auto* ptr2 = stack_allocator.Allocate(256);
//     REQUIRE(ptr1 != nullptr);
//     REQUIRE(ptr2 != nullptr);
//     REQUIRE(stack_allocator.GetUsedMemory() == 768);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 2);
//     stack_allocator.Free(ptr2);
//     REQUIRE(stack_allocator.GetUsedMemory() == 512);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 1);
//     stack_allocator.Free(ptr1);
//     REQUIRE(stack_allocator.GetUsedMemory() == 0);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 0);
// }

// TEST_CASE("Stack allocator works with multiple allocations and alignment", "[stack_allocator]")
// {
//     StackAllocator stack_allocator(1024);
//     auto* ptr1 = stack_allocator.Allocate(512, 16);
//     auto* ptr2 = stack_allocator.Allocate(256, 16);
//     REQUIRE(ptr1 != nullptr);
//     REQUIRE(ptr2 != nullptr);
//     REQUIRE(stack_allocator.GetUsedMemory() == 768);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 2);
//     stack_allocator.Free(ptr2);
//     REQUIRE(stack_allocator.GetUsedMemory() == 512);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 1);
//     stack_allocator.Free(ptr1);
//     REQUIRE(stack_allocator.GetUsedMemory() == 0);
//     REQUIRE(stack_allocator.GetAllocationsCount() == 0);
// }
