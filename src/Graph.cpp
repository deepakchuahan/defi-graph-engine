#include "Graph.hpp"
#include <stdexcept>

Graph::Graph(size_t v_count, ArenaAllocator& sys_mem) 
    : v_qty(v_count) {
    
    u64_chunks_per_row = (v_count + 63) >> 6;
    size_t block_bytes = v_qty * u64_chunks_per_row * sizeof(uint64_t);
    
    flat_bit_grid = static_cast<uint64_t*>(sys_mem.allocate(block_bytes, alignof(uint64_t)));
    if (!flat_bit_grid) {
        throw std::bad_alloc();
    }
    
    for (size_t idx = 0; idx < (v_qty * u64_chunks_per_row); ++idx) {
        flat_bit_grid[idx] = 0;
    }
}
