#include <iostream>
#include <vector>
#include <queue>

constexpr std::size_t MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> in;
    std::vector<std::size_t> dp;
    std::queue<std::size_t> q;
    std::size_t n, m, a, b;

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

    dp[0] = 1;

    for (std::size_t i = 0; i < n; ++i) {
        if (!in[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto& u : graph[v]) {
            dp[u] = (dp[u] + dp[v]) % MOD;

            if (!(--in[u])) {
                q.push(u);
            }
        }
    }

    std::cout << dp[n - 1] << "\n";
    return 0;
}