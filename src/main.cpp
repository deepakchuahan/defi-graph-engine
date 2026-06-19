#include "ArenaAllocator.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Instantiate 1MB Arena
    ArenaAllocator arena(1024 * 1024);

    // Test Case 1: Sequential Allocation & Alignment
    void* p1 = arena.allocate(17, 8); 
    assert(p1 != nullptr);
    assert(reinterpret_cast<uintptr_t>(p1) % 8 == 0);

    void* p2 = arena.allocate(8, 8);
    assert(p2 != nullptr);
    assert(reinterpret_cast<uintptr_t>(p2) % 8 == 0);
    assert(static_cast<std::byte*>(p2) >= static_cast<std::byte*>(p1) + 17);

    // Test Case 2: Reset behavior
    arena.reset();
    void* p3 = arena.allocate(17, 8);
    assert(p3 == p1); // Must reuse exact same starting boundary

    std::cout << "[PASS] Phase 1: Arena Allocator functionality verified." << std::endl;
    return 0;
}
