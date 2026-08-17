#ifndef CS509_CSR_HPP
#define CS509_CSR_HPP

#include <cstdint>
#include <stdexcept>
#include <vector>

struct AdjEdge {
    int to;
    long long capacity;
};

struct CSRGraph {
    int V = 0;
    int E = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<long long> values;
};

inline CSRGraph adjacencyListToCSR(
    int V,
    const std::vector<std::vector<AdjEdge>>& adj
) {
    if (V < 0 || static_cast<int>(adj.size()) != V) {
        throw std::runtime_error("Invalid adjacency list size.");
    }

    CSRGraph g;
    g.V = V;
    g.row_ptr.resize(V + 1, 0);

    for (int u = 0; u < V; ++u) {
        g.row_ptr[u + 1] = g.row_ptr[u] + static_cast<int>(adj[u].size());
    }

    g.E = g.row_ptr[V];
    g.col_idx.resize(g.E);
    g.values.resize(g.E);

    int k = 0;
    for (int u = 0; u < V; ++u) {
        for (const auto& e : adj[u]) {
            g.col_idx[k] = e.to;
            g.values[k] = e.capacity;
            ++k;
        }
    }

    return g;
}

#endif
