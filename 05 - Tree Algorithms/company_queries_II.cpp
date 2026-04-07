#include <iostream>
#include <vector>

inline std::size_t calculate_k(std::size_t n) {
    std::size_t k = 1, power = 1;

    while (power < n) {
        power <<= 1;
        ++k;
    }

    return k;
}

void calculate_depth(std::size_t v, std::vector<std::size_t>& depth,
                     std::vector<std::vector<std::size_t>> const& graph) {
    for (auto const& u : graph[v]) {
        depth[u] = depth[v] + 1;
        calculate_depth(u, depth, graph);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::size_t>> graph;
    std::vector<std::size_t> depth;
    std::vector<std::vector<std::size_t>> ancestor;
    std::size_t n, q, k, x, y;

    std::cin >> n >> q;

    graph.resize(n);
    depth.resize(n);
    ancestor.resize(n);

    k = calculate_k(n) + 1;
    for (auto& v : ancestor) {
        v.resize(k);
    }

    ancestor[0][0] = 0;

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> ancestor[i][0];
        --ancestor[i][0];
        graph[ancestor[i][0]].push_back(i);
    }

    for (std::size_t l = 1; l < k; ++l) {
        for (std::size_t i = 0; i < n; ++i) {
            ancestor[i][l] = ancestor[ancestor[i][l - 1]][l - 1];
        }
    }

    calculate_depth(0, depth, graph);

    while (q--) {
        std::cin >> x >> y;
        --x; --y;

        if (depth[x] < depth[y]) {
            std::swap(x, y);
        }

        for (std::size_t l = k - 1; l <= k; --l) {
            if (depth[x] == depth[y]) {
                break;
            }

            if (depth[ancestor[x][l]] >= depth[y]) {
                x = ancestor[x][l];
            }
        }

        if (x == y) {
            std::cout << x + 1 << "\n";
            continue;
        }

        for (std::size_t l = k - 1; l <= k; --l) {
            if (ancestor[x][l] != ancestor[y][l]) {
                x = ancestor[x][l];
                y = ancestor[y][l];
            }
        }

        std::cout << ancestor[x][0] + 1 << "\n";
    }

    return 0;
}