#include "ArenaAllocator.hpp"
#include <new>
#include <cstdlib>

ArenaAllocator::ArenaAllocator(size_t total_size) 
    : mem_ptr(nullptr), mem_cap(total_size), mem_off(0) {
    if (total_size > 0) {
        mem_ptr = static_cast<std::byte*>(std::malloc(total_size));
        if (!mem_ptr) {
            throw std::bad_alloc();
        }
    }
}

ArenaAllocator::~ArenaAllocator() {
    std::free(mem_ptr);
}

void* ArenaAllocator::allocate(size_t bytes, size_t alignment) {
    uintptr_t curr_addr = reinterpret_cast<uintptr_t>(mem_ptr + mem_off);
    uintptr_t mask = alignment - 1;
    uintptr_t aligned_addr = (curr_addr + mask) & ~mask;
    
    size_t next_off = aligned_addr - reinterpret_cast<uintptr_t>(mem_ptr) + bytes;
    if (next_off > mem_cap) {
        return nullptr;
    }
    
    mem_off = next_off;
    return reinterpret_cast<void*>(aligned_addr);
}

void ArenaAllocator::reset() {
    mem_off = 0;
}
