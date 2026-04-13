#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> dp;
std::vector<std::size_t> res;

void dfs1(std::size_t v, std::size_t p, std::size_t d) {
    res[0] += d;
    dp[v] = 1;

    for (auto const& u : graph[v]) {
        if (u != p) {
            dfs1(u, v, d + 1);
            dp[v] += dp[u];
        }
    }
}

void dfs2(std::size_t v, std::size_t p, std::size_t n) {
    for (auto const& u : graph[v]) {
        if (u != p) {
            res[u] = res[v] + n - 2 * dp[u];
            dfs2(u, v, n);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, a, b;
    
    std::cin >> n;
    graph.resize(n);
    dp.resize(n);
    res.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs1(0, 0, 0);
    dfs2(0, 0, n);

    for (auto const& r : res) {
        std::cout << r << " ";
    }

    std::cout << "\n";
    return 0;
}