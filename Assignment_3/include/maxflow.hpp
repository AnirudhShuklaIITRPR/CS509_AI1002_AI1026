#ifndef CS509_MAXFLOW_HPP
#define CS509_MAXFLOW_HPP

#include "csr.hpp"
#include <cstdint>
#include <vector>

struct CutEdge {
    int from;
    int to;
    long long capacity;
};

struct MaxflowResult {
    long long max_flow = 0;
    long long min_cut_capacity = 0;
    std::vector<int> source_side;
    std::vector<int> sink_side;
    std::vector<CutEdge> cut_edges;
};

MaxflowResult dinicMaxflowMincut(const CSRGraph& graph, int source, int sink);

#endif
