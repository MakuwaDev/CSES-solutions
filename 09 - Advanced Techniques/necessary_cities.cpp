#include <iostream>
#include <vector>

std::size_t timer = 0;
std::vector<std::vector<std::size_t>> graph;
std::vector<bool> vis;
std::vector<std::size_t> entry;
std::vector<std::size_t> low;
std::vector<bool> is_cut;

void dfs(std::size_t v, std::size_t p = -1) {
    std::size_t children = 0;
    
    vis[v] = true;
    entry[v] = low[v] = timer++;

    for (auto const& u : graph[v]) {
        if (u == p) {
            continue;
        }

        if (vis[u]) {
            low[v] = std::min(low[v], entry[u]);
        } else {
            dfs(u, v);
            low[v] = std::min(low[v], low[u]);

            if (low[u] >= entry[v] && p != static_cast<std::size_t>(-1)) {
                is_cut[v] = true;
            }

            ++children;
        }
    }

    if (p == static_cast<std::size_t>(-1) && children > 1) {
        is_cut[v] = true;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;
    std::vector<std::size_t> res;
    
    std::cin >> n >> m;

    graph.resize(n);
    vis.resize(n);
    entry.resize(n);
    low.resize(n);
    is_cut.resize(n);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0);

    for (std::size_t i = 0; i < n; ++i) {
        if (is_cut[i]) {
            res.push_back(i);
        }
    }

    std::cout << res.size() << "\n";
    for (auto const& v : res) {
        std::cout << v + 1 << " ";
    }

    std::cout << "\n";
    return 0;
}