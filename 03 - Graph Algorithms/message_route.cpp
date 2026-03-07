#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> prev;
    std::queue<std::size_t> q;
    std::vector<std::size_t> path;

    std::size_t n, m, a, b;
    std::cin >> n >> m;

    graph.resize(n + 1);
    prev.resize(n + 1);
    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    q.push(1);
    prev[1] = 1;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto const& u : graph[v]) {
            if (!prev[u]) {
                prev[u] = v;
                q.push(u);
            }
        }
    }

    prev[1] = 0;
    while (prev[n]) {
        path.push_back(n);
        n = prev[n];
    }

    if (path.empty()) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        std::cout << path.size() + 1 << "\n1";

        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << " " << *it;
        }
    }

    return 0;
}