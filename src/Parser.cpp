#include "Parser.hpp"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>

FastLoader::FastLoader(const std::string& pth) 
    : f_path(pth.c_str()), fd_desc(-1), f_sz(0), m_region(nullptr) {
    
    fd_desc = open(f_path, O_RDONLY);
    if (fd_desc == -1) throw std::runtime_error("F_ERR");

    struct stat stat_b;
    if (fstat(fd_desc, &stat_b) == -1) throw std::runtime_error("ST_ERR");
    f_sz = stat_b.st_size;

    m_region = static_cast<char*>(mmap(nullptr, f_sz, PROT_READ, MAP_PRIVATE, fd_desc, 0));
    if (m_region == MAP_FAILED) throw std::runtime_error("MAP_ERR");
}

FastLoader::~FastLoader() {
    if (m_region != MAP_FAILED) munmap(m_region, f_sz);
    if (fd_desc != -1) close(fd_desc);
}

void FastLoader::ingest_edges(Graph& g_tgt) {
    size_t cur_pos = 0;
    while (cur_pos < f_sz) {
        size_t n_u = 0;
        while (cur_pos < f_sz && m_region[cur_pos] >= '0' && m_region[cur_pos] <= '9') {
            n_u = n_u * 10 + (m_region[cur_pos] - '0');
            ++cur_pos;
        }
        
        while (cur_pos < f_sz && (m_region[cur_pos] == ' ' || m_region[cur_pos] == '\t')) {
            ++cur_pos;
        }

        size_t n_v = 0;
        while (cur_pos < f_sz && m_region[cur_pos] >= '0' && m_region[cur_pos] <= '9') {
            n_v = n_v * 10 + (m_region[cur_pos] - '0');
            ++cur_pos;
        }

        while (cur_pos < f_sz && (m_region[cur_pos] == '\n' || m_region[cur_pos] == '\r')) {
            ++cur_pos;
        }

        if (n_u != n_v) {
            g_tgt.establish_link(n_u, n_v);
        }
    }
}
