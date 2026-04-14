#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::vector<std::size_t>> graph_t;
std::vector<bool> vis;
std::vector<std::size_t> out;
std::vector<std::size_t> order;

void dfs1(std::size_t v) {
    vis[v] = true;

    for (auto const& u : graph[v]) {
        if (!vis[u]) {
            dfs1(u);
        }
    }

    out.push_back(v);
}

void dfs2(std::size_t v, std::size_t id) {
    order[v] = id;

    for (auto const& u : graph_t[v]) {
        if (!order[u]) {
            dfs2(u, id);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<bool> assignment;
    std::size_t n, m, x, y, id = 0;
    char cx, cy;

    std::cin >> m >> n;

    graph.resize(2 * n);
    graph_t.resize(2 * n);
    vis.resize(2 * n);
    order.resize(2 * n);
    assignment.resize(n);

    while (m--) {
        std::cin >> cx >> x >> cy >> y;
        --x; --y;

        x = 2 * x ^ (cx == '+');
        y = 2 * y ^ (cy == '+');

        graph[x ^ 1].push_back(y);
        graph[y ^ 1].push_back(x);

        graph_t[x].push_back(y ^ 1);
        graph_t[y].push_back(x ^ 1);
    }

    for (std::size_t v = 0; v < 2 * n; ++v) {
        if (!vis[v]) {
            dfs1(v);
        }
    }

    while (!out.empty()) {
        auto v = out.back();
        out.pop_back();

        if (!order[v]) {
            dfs2(v, ++id);
        }
    }

    for (std::size_t i = 0; i < 2 * n; i += 2) {
        if (order[i] == order[i + 1]) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }

        assignment[i / 2] = order[i] < order[i + 1];
    }

    for (auto const& x : assignment) {
        std::cout << (x ? "+ " : "- ");
    }

    std::cout << "\n";
    return 0;
}