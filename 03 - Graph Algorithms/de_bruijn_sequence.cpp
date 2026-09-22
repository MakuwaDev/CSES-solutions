#include <iostream>
#include <vector>

std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
std::vector<std::size_t> id;
std::vector<bool> vis;
std::vector<std::size_t> euler;

void dfs(std::size_t v) {
    while (id[v] < graph[v].size()) {
        std::size_t idx = id[v]++;

        if (!vis[graph[v][idx].second]) {
            vis[graph[v][idx].second] = true;
            dfs(graph[v][idx].first);
            euler.push_back(idx);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t l, n, m;
    std::string res = "";
    
    std::cin >> l;

    n = 1 << (l - 1);
    m = 2 * n;

    graph.resize(n);
    id.resize(n);
    vis.resize(m);

    for (std::size_t i = 0; i < n; ++i) {
        graph[i].push_back({(2 * i) % n, --m});
        graph[i].push_back({(2 * i + 1) % n, --m});
    }

    dfs(0);

    for (auto it = euler.rbegin(); it != euler.rend(); ++it) {
        res += std::to_string(*it);
    }

    res += res.substr(0, l - 1);

    std::cout << res << "\n";
    return 0;
}