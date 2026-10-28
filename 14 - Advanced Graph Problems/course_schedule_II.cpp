#include <iostream>
#include <vector>
#include <queue>
#include <ranges>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;
    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> res;
    std::vector<std::size_t> in;
    std::priority_queue<std::size_t> q;

    std::cin >> n >> m;

    graph.resize(n);
    in.resize(n, 0);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;

        ++in[a];
        graph[b].push_back(a);
    }

    for (std::size_t v = 0; v < n; ++v) {
        if (!in[v]) {
            q.push(v);
        }
    }

    while (!q.empty()) {
        auto v = q.top();
        q.pop();

        res.push_back(v);

        for (auto const& u : graph[v]) {
            if (!(--in[u])) {
                q.push(u);
            }
        }
    }

    for (auto const& v : res | std::views::reverse) {
        std::cout << v + 1 << " ";
    }

    std::cout << "\n";
    return 0;
}