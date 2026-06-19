#include "Solver.hpp"
#include <algorithm>

ExactEngine::ExactEngine(const Graph& g_in, size_t v_max) 
    : g_ctx(g_in), v_tot(v_max), min_ans(v_max) {}

bool ExactEngine::verify_cov(const std::vector<uint8_t>& c_state) const {
    for (size_t alpha = 0; alpha < v_tot; ++alpha) {
        for (size_t beta = alpha + 1; beta < v_tot; ++beta) {
            if (g_ctx.is_linked(alpha, beta)) {
                if (c_state[alpha] == 0 && c_state[beta] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void ExactEngine::rec_explore(size_t c_idx, size_t cur_sz, std::vector<uint8_t>& c_state) {
    if (cur_sz >= min_ans) {
        return;
    }
    
    if (c_idx == v_tot) {
        if (verify_cov(c_state)) {
            min_ans = std::min(min_ans, cur_sz);
        }
        return;
    }

    c_state[c_idx] = 1;
    rec_explore(c_idx + 1, cur_sz + 1, c_state);

    c_state[c_idx] = 0;
    rec_explore(c_idx + 1, cur_sz, c_state);
}

size_t ExactEngine::run_engine() {
    std::vector<uint8_t> init_state(v_tot, 0);
    rec_explore(0, 0, init_state);
    return min_ans;
}
