#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::size_t res = 0;

std::vector<std::size_t> dfs(std::size_t v, std::size_t p, std::size_t k) {
    std::vector<std::size_t> main_vec;
    std::size_t dist, needed;
    
    for (auto const& u : graph[v]) {
        if (u == p) {
            continue;
        }

        std::vector<std::size_t> child_vec = dfs(u, v, k);

        if (child_vec.size() > main_vec.size()) {
            std::swap(main_vec, child_vec);
        }

        for (std::size_t i = 0; i < child_vec.size(); ++i) {
            dist = child_vec.size() - i;

            if (dist <= k) {
                needed = k - dist;

                if (needed > 0 && needed <= main_vec.size()) {
                    res += child_vec[i] * main_vec[main_vec.size() - needed];
                }
            }
        }

        for (std::size_t i = 0; i < child_vec.size(); ++i) {
            main_vec[main_vec.size() - child_vec.size() + i] += child_vec[i];
        }
    }

    if (k <= main_vec.size() && k > 0) {
        res += main_vec[main_vec.size() - k];
    }

    main_vec.push_back(1);

    return main_vec;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, a, b;

    std::cin >> n >> k;

    graph.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0, 0, k);

    std::cout << res << "\n";
    return 0;
}