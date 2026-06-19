#pragma once
#include "ArenaAllocator.hpp"
#include <cstdint>
#include <cstddef>

class Graph {
private:
    uint64_t* flat_bit_grid;
    size_t v_qty;
    size_t u64_chunks_per_row;

public:
    Graph(size_t v_count, ArenaAllocator& sys_mem);
    void establish_link(size_t n_alpha, size_t n_beta);
    bool is_linked(size_t n_alpha, size_t n_beta) const;
    int fetch_degree(size_t t_node) const;
};
