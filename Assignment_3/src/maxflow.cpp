#include "maxflow.hpp"

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>

namespace {

struct Edge {
    int to;
    int rev;
    long long cap;
};

class Dinic {
    int n_;
    std::vector<std::vector<Edge>> g_;
    std::vector<int> level_;
    std::vector<int> it_;

public:
    explicit Dinic(int n)
        : n_(n), g_(n), level_(n), it_(n) {}

    void addEdge(int u, int v, long long cap) {
        Edge a{v, static_cast<int>(g_[v].size()), cap};
        Edge b{u, static_cast<int>(g_[u].size()), 0};
        g_[u].push_back(a);
        g_[v].push_back(b);
    }

    bool bfs(int s, int t) {
        std::fill(level_.begin(), level_.end(), -1);
        std::queue<int> q;
        level_[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& e : g_[u]) {
                if (e.cap > 0 && level_[e.to] == -1) {
                    level_[e.to] = level_[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level_[t] != -1;
    }

    long long dfs(int u, int t, long long pushed) {
        if (pushed == 0) return 0;
        if (u == t) return pushed;

        for (int& i = it_[u]; i < static_cast<int>(g_[u].size()); ++i) {
            Edge& e = g_[u][i];
            if (e.cap <= 0 || level_[e.to] != level_[u] + 1) continue;

            long long send = dfs(
                e.to, t, std::min(pushed, e.cap)
            );

            if (send == 0) continue;

            e.cap -= send;
            g_[e.to][e.rev].cap += send;
            return send;
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long flow = 0;
        const long long INF = std::numeric_limits<long long>::max() / 4;

        while (bfs(s, t)) {
            std::fill(it_.begin(), it_.end(), 0);
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    std::vector<char> reachableFrom(int s) const {
        std::vector<char> vis(n_, false);
        std::queue<int> q;
        vis[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& e : g_[u]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
};

} // namespace

MaxflowResult dinicMaxflowMincut(
    const CSRGraph& graph,
    int source,
    int sink
) {
    if (graph.V <= 0) {
        throw std::runtime_error("Graph must contain at least one vertex.");
    }
    if (source < 0 || source >= graph.V ||
        sink < 0 || sink >= graph.V) {
        throw std::runtime_error("Source/sink vertex is out of range.");
    }
    if (source == sink) {
        throw std::runtime_error("Source and sink must be different.");
    }

    // This initialization is deliberately inside the algorithm call.
    // Assignment 3 requires residual-network initialization to be timed.
    Dinic dinic(graph.V);

    for (int u = 0; u < graph.V; ++u) {
        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) {
            const int v = graph.col_idx[i];
            const long long cap = graph.values[i];

            if (v < 0 || v >= graph.V) {
                throw std::runtime_error("Invalid edge endpoint.");
            }
            if (cap < 0) {
                throw std::runtime_error("Negative capacity is invalid.");
            }
            if (cap > 0) {
                dinic.addEdge(u, v, cap);
            }
        }
    }

    MaxflowResult result;
    result.max_flow = dinic.maxFlow(source, sink);

    // Required minimum-cut extraction is part of the timed algorithm.
    const std::vector<char> reachable = dinic.reachableFrom(source);

    for (int v = 0; v < graph.V; ++v) {
        if (reachable[v]) result.source_side.push_back(v);
        else result.sink_side.push_back(v);
    }

    for (int u = 0; u < graph.V; ++u) {
        if (!reachable[u]) continue;

        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) {
            int v = graph.col_idx[i];
            long long cap = graph.values[i];

            if (cap > 0 && !reachable[v]) {
                result.cut_edges.push_back({u, v, cap});
                result.min_cut_capacity += cap;
            }
        }
    }

    return result;
}
