#pragma once
#include "Graph.hpp"
#include <vector>
#include <cstdint>
#include <cstddef>

class ExactEngine {
private:
    const Graph& g_ctx;
    size_t v_tot;
    size_t min_ans;

    bool verify_cov(const std::vector<uint8_t>& c_state) const;
    void rec_explore(size_t c_idx, size_t cur_sz, std::vector<uint8_t>& c_state);

public:
    explicit ExactEngine(const Graph& g_in, size_t v_max);
    size_t run_engine();
};

