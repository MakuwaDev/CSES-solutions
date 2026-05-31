#include <iostream>
#include <vector>

std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
std::vector<std::size_t> id;
std::vector<bool> vis;
std::vector<std::size_t> euler;

void dfs(std::size_t v) {
    while (id[v] < graph[v].size()) {
        std::size_t idx = id[v];
        ++id[v];

        if (!vis[graph[v][idx].second]) {
            vis[graph[v][idx].second] = true;
            dfs(graph[v][idx].first);
        }
    }

    euler.push_back(v);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;
    
    std::cin >> n >> m;

    graph.resize(n + 1);
    id.resize(n + 1);
    vis.resize(m + 1);

    for (std::size_t i = 1; i <= m; ++i) {
        std::cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }

    for (std::size_t i = 1; i <= n; ++i) {
        if (graph[i].size() % 2) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(1);

    for (std::size_t e = 1; e <= m; ++e) {
        if (!vis[e]) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (auto it = euler.rbegin(); it != euler.rend(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n";
    return 0;
}