#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> in;
    std::vector<std::size_t> order;
    std::queue<std::size_t> q;
    std::size_t n, m, a, b;

    std::cin >> n >> m;
    graph.resize(n);
    in.resize(n);

    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        ++in[b];
    }


    for (std::size_t i = 0; i < n; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        order.push_back(u);

        for (auto const& v : graph[u]) {
            --in[v];
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    if (order.size() == n) {
        for (auto const& x : order) {
            std::cout << x + 1 << " ";
        }
    } else {
        std::cout << "IMPOSSIBLE";
    }

    std::cout << "\n";
    return 0;
}