#include <iostream>
#include <vector>

constexpr std::size_t INF = 1e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> t;
    std::vector<std::size_t> dist;
    std::vector<std::size_t> stack;
    std::vector<bool> on;
    std::size_t n;

    std::cin >> n;
    
    t.resize(n);
    dist.resize(n, INF);
    on.resize(n, false);

    for (auto& x : t) {
        std::cin >> x;
        --x;
    }

    for (std::size_t v = 0; v < n; ++v) {
        std::size_t x = v;
        bool cycle;

        while (true) {
            if (dist[x] != INF) {
                cycle = false;
                break;
            } else if (on[x]) {
                cycle = true;
                break;
            }

            stack.push_back(x);
            on[x] = true;
            x = t[x];
        }

        if (cycle) {
            std::size_t y = x, l = 1;
            
            while (stack[stack.size() - l] != y) {
                ++l;
            }

            while (true) {
                x = stack.back();
                stack.pop_back();

                dist[x] = l;
                on[x] = false;

                if (x == y) {
                    break;
                }
            }
        }

        while (!stack.empty()) {
            x = stack.back();
            stack.pop_back();

            dist[x] = dist[t[x]] + 1;
            on[x] = false;
        }
    }

    for (auto const& x : dist) {
        std::cout << x << " ";
    }

    std::cout << "\n";
    return 0;
}