
#include "ArenaAllocator.hpp"
#include "Graph.hpp"
#include "Solver.hpp"
#include <iostream>
#include <cassert>

int main() {
    ArenaAllocator sys_arena(1024 * 1024);
    size_t net_size = 5;
    Graph net_graph(net_size, sys_arena);
    
    net_graph.establish_link(0, 1);
    net_graph.establish_link(0, 2);
    net_graph.establish_link(1, 2);
    net_graph.establish_link(2, 3);
    net_graph.establish_link(3, 4);

    ExactEngine mvc_solver(net_graph, net_size);
    size_t opt_wallets = mvc_solver.run_engine();

    assert(opt_wallets == 3); 

    std::cout << "[PASS] Phase 3: Exact Solver logic verified. Min wallets: " << opt_wallets << std::endl;
    return 0;
}
