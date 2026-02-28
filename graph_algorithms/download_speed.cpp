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

uint64_t bfs(Graph& g, std::size_t source, std::size_t sink,
    std::vector<std::pair<std::size_t, std::size_t>>& parent) {

    std::fill(parent.begin(), parent.end(), std::make_pair(INF, 0));
    
    std::queue<std::size_t> q;
    q.push(source);
    parent[source] = {source, 0};

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        for (std::size_t i = 0; i < g[u].size(); ++i) {
            Edge& e = g[u][i];

            if (parent[e.to].first == INF && e.capacity > 0) {
                parent[e.to] = {u, i};

                if (e.to == sink) {
                    break;
                }

                q.push(e.to);
            }
        }
    }

    if (parent[sink].first == INF) {
        return 0;
    }

    uint64_t path_flow = INF;

    for (std::size_t v = sink; v != source; ) {
        auto [u, id] = parent[v];
        path_flow = std::min(path_flow, g[u][id].capacity);
        v = u;
    }

    for (std::size_t v = sink; v != source; ) {
        auto [u, id] = parent[v];
        g[u][id].capacity -= path_flow;
        g[v][g[u][id].reverse].capacity += path_flow;
        v = u;
    }

    return path_flow;
}

uint64_t edmonds_karp(Graph& g, std::size_t source, std::size_t sink) {
    uint64_t max_flow = 0;
    std::vector<std::pair<std::size_t, std::size_t>> parent(g.size());

    while (uint64_t pushed = bfs(g, source, sink, parent)) {
        max_flow += pushed;
    }

    return max_flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::size_t n, m;
    Graph graph;

    std::cin >> n >> m;
    graph.resize(n);

    for (uint32_t i = 0; i < m; ++i) {
        std::size_t u, v;
        uint64_t cap;
        std::cin >> u >> v >> cap;
        --u; --v;
        add_edge(graph, u, v, cap);
    }

    uint64_t max_flow = edmonds_karp(graph, 0, n - 1);
    std::cout << max_flow << "\n";

    return 0;
}
