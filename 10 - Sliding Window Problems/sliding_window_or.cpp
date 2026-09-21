#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, x, a, b, c, res = 0;
    std::vector<std::pair<std::size_t, std::size_t>> in, out;

    std::cin >> n >> k;
    std::cin >> x >> a >> b >> c;

    for (std::size_t i = 1; i <= n; ++i) {
        in.push_back({x, in.empty() ? x : x | in.back().second});

        if (i > k) {
            if (out.empty()) {
                while (!in.empty()) {
                    out.push_back({in.back().first, out.empty() ? in.back().first : out.back().second | in.back().first});
                    in.pop_back();
                }
            }

            out.pop_back();
        }

        if (i >= k) {
            res ^= ((in.empty() ? 0 : in.back().second) | (out.empty() ? 0 : out.back().second));
        }

        x = (a * x + b) % c;
    }

    std::cout << res << "\n";
    return 0;
}