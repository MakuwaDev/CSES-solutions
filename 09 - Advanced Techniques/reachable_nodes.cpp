#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <ranges>

constexpr std::size_t MAXN = 5e4 + 4;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;
    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> in;
    std::vector<std::size_t> order;
    std::vector<std::bitset<MAXN>> dp;
    std::queue<std::size_t> q;

    std::cin >> n >> m;

    graph.resize(n);
    in.resize(n);
    dp.resize(n);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        ++in[b];
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (!in[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        order.push_back(v);

        for (auto const& u : graph[v]) {
            if (!(--in[u])) {
                q.push(u);
            }
        }
    }

    for (auto const& v : order | std::views::reverse) {
        dp[v][v] = 1;

        for (auto const& u : graph[v]) {
            dp[v] |= dp[u];
        }
    }

    for (auto const& b : dp) {
        std::cout << b.count() << " ";
    }

    std::cout << "\n";
    return 0;
}