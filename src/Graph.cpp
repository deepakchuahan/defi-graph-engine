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

void Graph::establish_link(size_t n_alpha, size_t n_beta) {
    size_t alpha_blk = n_alpha * u64_chunks_per_row + (n_beta >> 6);
    size_t beta_blk = n_beta * u64_chunks_per_row + (n_alpha >> 6);
    
    uint64_t alpha_mask = 1ULL << (n_beta & 63);
    uint64_t beta_mask = 1ULL << (n_alpha & 63);
    
    flat_bit_grid[alpha_blk] |= alpha_mask;
    flat_bit_grid[beta_blk] |= beta_mask;
}

bool Graph::is_linked(size_t n_alpha, size_t n_beta) const {
    size_t alpha_blk = n_alpha * u64_chunks_per_row + (n_beta >> 6);
    uint64_t bit_mask = 1ULL << (n_beta & 63);
    return (flat_bit_grid[alpha_blk] & bit_mask) != 0;
}

int Graph::fetch_degree(size_t t_node) const {
    int d_count = 0;
    size_t r_start = t_node * u64_chunks_per_row;
    for (size_t c_idx = 0; c_idx < u64_chunks_per_row; ++c_idx) {
        d_count += __builtin_popcountll(flat_bit_grid[r_start + c_idx]);
    }
    return d_count;
}

