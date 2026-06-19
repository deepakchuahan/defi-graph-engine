#pragma once
#include <cstddef>
#include <cstdint>

class ArenaAllocator {
private:
    std::byte* mem_ptr;
    size_t mem_cap;
    size_t mem_off;

public:
    explicit ArenaAllocator(size_t total_size);
    ~ArenaAllocator();

    ArenaAllocator(const ArenaAllocator&) = delete;
    ArenaAllocator& operator=(const ArenaAllocator&) = delete;

    void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t));
    void reset();
};
