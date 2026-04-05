#include <iostream>
#include <vector>

std::vector<std::vector<std::size_t>> graph;
std::vector<std::size_t> state;
std::vector<std::size_t> stack;

bool dfs(std::size_t v) {
    stack.push_back(v);
    state[v] = 1;

    for (auto const& u : graph[v]) {
        if (state[u] == 0) {
            if (dfs(u)) {
                return true;
            }
        } else if (state[u] == 1) {
            stack.push_back(u);
            return true;
        }
    }

    state[v] = 2;
    stack.pop_back();

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> cycle;
    std::size_t n, m, a, b;

    std::cin >> n >> m;
    
    graph.resize(n);
    state.resize(n);

    while (m--) {
        std::cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (state[i] == 0 && dfs(i)) {
            a = stack.back();
            cycle.push_back(a);
            stack.pop_back();

            while (stack.back() != a) {
                cycle.push_back(stack.back());
                stack.pop_back();
            }

            cycle.push_back(a);

            std::cout << cycle.size() << "\n";
            for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
                std::cout << *it + 1 << " ";
            }

            std::cout << "\n";
            return 0;
        }
    }

    std::cout << "IMPOSSIBLE\n";
    return 0;
}