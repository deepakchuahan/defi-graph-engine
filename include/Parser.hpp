#pragma once
#include "Graph.hpp"
#include <string>

class FastLoader {
private:
    const char* f_path;
    int fd_desc;
    size_t f_sz;
    char* m_region;

public:
    explicit FastLoader(const std::string& pth);
    ~FastLoader();
    void ingest_edges(Graph& g_tgt);
};
