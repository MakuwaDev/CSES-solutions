#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <queue>
 
constexpr std::uint64_t INF = std::numeric_limits<uint64_t>::max();
 
struct Edge {
    std::size_t to;
    std::size_t reverse;
    uint64_t capacity;
};
 
using Graph = std::vector<std::vector<Edge>>;
 
void add_edge(Graph& g, std::size_t u, std::size_t v, uint64_t cap) {
    Edge forward{v, g[v].size(), cap};
    Edge backward{u, g[u].size(), 0};
 
    g[u].push_back(forward);
    g[v].push_back(backward);
}
 
bool bfs(Graph& g, std::size_t source, std::size_t sink,
         std::vector<std::size_t>& level) {
    std::fill(level.begin(), level.end(), INF);
    std::queue<std::size_t> q;
 
    level[source] = 0;
    q.push(source);
 
    while (!q.empty()) {
        std::size_t u = q.front();
        q.pop();
 
        for (Edge const& e : g[u]) {
            if (e.capacity > 0 && level[e.to] == INF) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
 
    return level[sink] != INF;
}
 
 
uint64_t dfs(Graph& g, std::size_t u, std::size_t t, uint64_t pushed,
             std::vector<std::size_t>& level, std::vector<std::size_t>& ptr) {
    if (pushed == 0) {
        return 0;
    }
 
    if (u == t) {
        return pushed;
    }
 
    for (std::size_t& cid = ptr[u]; cid < g[u].size(); ++cid) {
        Edge& e = g[u][cid];
 
        if (e.capacity > 0 && level[e.to] == level[u] + 1) {
            uint64_t tr = dfs(g, e.to, t,std::min(pushed, e.capacity), level, ptr);
 
            if (tr == 0) {
                continue;
            }
 
            e.capacity -= tr;
            g[e.to][e.reverse].capacity += tr;
            return tr;
        }
    }
 
    return 0;
}
 
uint64_t dinic(Graph& g, std::size_t s, std::size_t t) {
    uint64_t flow = 0;
    std::vector<std::size_t> level(g.size());
 
    while (bfs(g, s, t, level)) {
        std::vector<std::size_t> ptr(g.size(), 0);
        while (uint64_t pushed = dfs(g, s, t, INF, level, ptr)) {
            flow += pushed;
        }
    }
 
    return flow;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::size_t n, m, k, a, b;
    Graph graph;

    std::cin >> n >> m >> k;

    graph.resize(n + m + 2);

    while (k--) {
        std::cin >> a >> b;
        add_edge(graph, a, n + b, 1);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        add_edge(graph, 0, i, 1);
    }

    for (std::size_t i = 1; i <= m; ++i) {
        add_edge(graph, n + i, n + m + 1, 1);
    }

    std::cout << dinic(graph, 0, n + m + 1) << "\n";

    for (std::size_t i = 1; i <= n; ++i) {
        for (auto& e : graph[i]) {
            if (e.capacity == 0 && e.to > n) {
                std::cout << i << " " << e.to - n << "\n";
            }
        }
    }

    return 0;
}