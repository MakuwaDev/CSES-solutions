#include <iostream>
#include <vector>
#include <queue>

void dfs(std::size_t v, std::vector<bool>& visited, std::vector<bool>& achieved,
         std::vector<std::vector<std::pair<std::size_t, std::size_t>>>& graph) {
    visited[v] = true;
    
    for (auto const& e : graph[v]) {
        achieved[e.second] = true;

        if (!visited[e.first]) {
            dfs(e.first, visited, achieved, graph);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
    std::vector<std::size_t> in;
    std::vector<std::size_t> dist;
    std::vector<std::size_t> prev;
    std::vector<bool> achieved;
    std::vector<bool> visited;
    std::queue<std::size_t> q;
    std::size_t n, m, a, b;

    std::cin >> n >> m;

    graph.resize(n);
    in.resize(n);
    dist.resize(n);
    prev.resize(n);
    achieved.resize(m);
    visited.resize(n);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back({b, m});
    }

    dfs(0, visited, achieved, graph);

    for (auto const& v : graph) {
        for (auto const& e : v) {
            if (achieved[e.second]) {
                ++in[e.first];
            }
        }
    }

    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto const& e : graph[v]) {
            if (dist[e.first] < dist[v] + 1) {
                dist[e.first] = dist[v] + 1;
                prev[e.first] = v;
            }

            if (--in[e.first] == 0) {
                q.push(e.first);
            }
        }
    }

    if (dist[n - 1]) {
        std::vector<std::size_t> path;
        a = n - 1;

        path.push_back(a);
        while (a != 0) {
            a = prev[a];
            path.push_back(a);
        }

        std::cout << dist[n - 1] + 1<< "\n";
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << *it + 1 << " ";
        }
    } else {
        std::cout << "IMPOSSIBLE";
    }

    std::cout << "\n";
    return 0;
}