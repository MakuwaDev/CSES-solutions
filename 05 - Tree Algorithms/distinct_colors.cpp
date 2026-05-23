#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> color;
std::vector<std::size_t> dp;
std::vector<std::set<std::size_t>> subtree;
std::vector<std::size_t> id;


void dfs(std::size_t v = 1, std::size_t p = 0) {
    subtree[id[v]].insert(color[v]);

    for (auto const& u : graph[v]) {
        if (u != p) {
            dfs(u, v);

            if (subtree[id[v]].size() < subtree[id[u]].size()) {
                std::swap(id[v], id[u]);
            }

            for (auto const& x : subtree[id[u]]) {
                subtree[id[v]].insert(x);
            }

            subtree[id[u]].clear();
        }
    }

    dp[v] = subtree[id[v]].size();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, a ,b;

    std::cin >> n;

    graph.resize(n + 1);
    color.resize(n + 1);
    dp.resize(n + 1);
    subtree.resize(n + 1);
    id.resize(n + 1);

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> color[i];
        id[i] = i;
    }

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs();

    for (auto it = ++dp.begin(); it != dp.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n";
    return 0;
}