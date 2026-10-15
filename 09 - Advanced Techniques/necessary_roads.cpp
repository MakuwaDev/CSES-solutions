#include <iostream>
#include <vector>

std::size_t timer = 0;
std::vector<std::vector<std::size_t>> graph;
std::vector<bool> vis;
std::vector<std::size_t> entry;
std::vector<std::size_t> low;
std::vector<std::pair<std::size_t, std::size_t>> res;

void dfs(std::size_t v, std::size_t p = -1) {
    vis[v] = true;
    entry[v] = low[v] = timer++;

    for (auto const& u : graph[v]) {
        if (vis[u]) {
            if (u == p) {
                continue;
            }

            low[v] = std::min(low[v], entry[u]);
        } else {
            dfs(u, v);
            low[v] = std::min(low[v], low[u]);

            if (low[u] > entry[v]) {
                res.push_back({v, u});
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;
    
    std::cin >> n >> m;

    graph.resize(n);
    vis.resize(n);
    entry.resize(n);
    low.resize(n);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0);

    std::cout << res.size() << "\n";
    for (auto const& e : res) {
        std::cout << e.first + 1 << " " << e.second + 1 << "\n";
    }

    return 0;
}