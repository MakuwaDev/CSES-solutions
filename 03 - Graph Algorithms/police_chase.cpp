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
    Edge backward{u, g[u].size(), cap};

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

uint64_t dinic(Graph& g, std::size_t s, std::size_t t, std::vector<std::size_t>& level) {
    uint64_t flow = 0;

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
    
    std::size_t n, m, u, v;
    Graph graph;
    std::vector<std::size_t> level;
    std::vector<std::pair<std::size_t, std::size_t>> edges;

    std::cin >> n >> m;

    graph.resize(n);
    level.resize(n, INF);

    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u; --v;

        edges.push_back({u, v});
        add_edge(graph, u, v, 1);
    }

    std::cout << dinic(graph, 0, n - 1, level) << "\n";

    for (auto const& edge : edges) {
        u = edge.first;
        v = edge.second;

        if ((level[u] != INF) != (level[v] != INF)) {
            std::cout << u + 1 << " " << v + 1 << "\n";
        }
    }

    return 0;
}