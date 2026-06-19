#include "Solver.hpp"
#include <algorithm>
#include <vector>

ExactEngine::ExactEngine(const Graph& g_in, size_t v_max) 
    : g_ctx(g_in), v_tot(v_max), min_ans(v_max) {}

bool ExactEngine::verify_cov(const std::vector<uint8_t>& st_arr) const {
    for (size_t alpha = 0; alpha < v_tot; ++alpha) {
        for (size_t beta = alpha + 1; beta < v_tot; ++beta) {
            if (g_ctx.is_linked(alpha, beta)) {
                if (st_arr[alpha] != 1 && st_arr[beta] != 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

void ExactEngine::rec_explore(size_t n_idx, size_t cur_sz, std::vector<uint8_t>& st_arr) {
    if (cur_sz >= min_ans) return;

    size_t trgt = v_tot;
    for (size_t iter = n_idx; iter < v_tot; ++iter) {
        if (st_arr[iter] == 0) {
            trgt = iter;
            break;
        }
    }

    if (trgt == v_tot) {
        if (verify_cov(st_arr)) {
            min_ans = std::min(min_ans, cur_sz);
        }
        return;
    }

    st_arr[trgt] = 1;
    rec_explore(trgt + 1, cur_sz + 1, st_arr);

    st_arr[trgt] = 2;
    std::vector<size_t> f_nbrs;
    bool p_valid = true;

    for (size_t nbr = 0; nbr < v_tot; ++nbr) {
        if (g_ctx.is_linked(trgt, nbr)) {
            if (st_arr[nbr] == 2) {
                p_valid = false;
                break;
            }
            if (st_arr[nbr] == 0) {
                st_arr[nbr] = 1;
                f_nbrs.push_back(nbr);
            }
        }
    }

    if (p_valid) {
        rec_explore(trgt + 1, cur_sz + f_nbrs.size(), st_arr);
    }

    st_arr[trgt] = 0;
    for (size_t fn : f_nbrs) {
        st_arr[fn] = 0;
    }
}

size_t ExactEngine::run_engine() {
    std::vector<uint8_t> init_st(v_tot, 0);
    rec_explore(0, 0, init_st);
    return min_ans;
}
