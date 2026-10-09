#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, ptr = 0, leaf;
    std::vector<std::size_t> code;
    std::vector<std::size_t> deg;
    std::vector<std::pair<std::size_t, std::size_t>> edges;

    std::cin >> n;

    code.resize(n - 2);
    deg.resize(n, 1);

    for (auto& v : code) {
        std::cin >> v;
        --v;
        ++deg[v];
    }

    while (deg[ptr] != 1) {
        ++ptr;
    }

    leaf = ptr;

    for (auto const& v : code) {
        edges.push_back({leaf, v});

        if (--deg[v] == 1 && v < ptr) {
            leaf = v;
        } else {
            ++ptr;

            while (deg[ptr] != 1) {
                ++ptr;
            }

            leaf = ptr;
        }
    }

    edges.push_back({leaf, n - 1});

    for (auto const& e : edges) {
        std::cout << e.first + 1 << " " << e.second + 1 << "\n";
    }

    return 0;
}