#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> in;
std::vector<std::size_t> out;
std::vector<std::size_t> start;
std::vector<std::size_t> res;

void dfs(std::size_t v) {
    while (start[v] < graph[v].size()) {
        dfs(graph[v][start[v]++]);
    }

    res.push_back(v);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b;

    std::cin >> n >> m;

    graph.resize(n);
    in.resize(n);
    out.resize(n);
    start.resize(n);

    for (std::size_t _ = 0; _ < m; ++_) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        ++in[b];
        ++out[a];
    }

    for (std::size_t i = 1; i < n - 1; ++i) {
        if (in[i] != out[i]) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    if (out.front() - in.front() != 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    if (in.back() - out.back() != 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    dfs(0);

    if (res.size() != m + 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;   
    }

    for (auto it = res.rbegin(); it != res.rend(); ++it) {
        std::cout << (*it) + 1 << " ";
    }

    std::cout << "\n";
    return 0;
}