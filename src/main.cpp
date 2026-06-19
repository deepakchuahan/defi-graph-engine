#include "ArenaAllocator.hpp"
#include "Graph.hpp"
#include "Solver.hpp"
#include "Parser.hpp"
#include <iostream>

int main() {
    ArenaAllocator sys_arena(1024 * 1024);
    size_t max_nodes = 5; 
    Graph defi_net(max_nodes, sys_arena);
    
    FastLoader snap_reader("../data/snap_sample.txt");
    snap_reader.ingest_edges(defi_net);

    ExactEngine risk_analyzer(defi_net, max_nodes);
    size_t min_wallets = risk_analyzer.run_engine();

    std::cout << "[PASS] Engine Complete. MVC Result: " << min_wallets << std::endl;
    return 0;
}
