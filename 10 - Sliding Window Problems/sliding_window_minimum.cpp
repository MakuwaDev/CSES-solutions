#include <iostream>
#include <deque>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, x, a, b, c, res = 0;
    std::deque<std::pair<std::size_t, std::size_t>> q;

    std::cin >> n >> k;
    std::cin >> x >> a >> b >> c;

    for (std::size_t i = 1; i <= n; ++i) {
        while (!q.empty() && q.back().second >= x) {
            q.pop_back();
        }

        q.push_back({i, x});

        if (i > k) {
            while (q.front().first < i - k + 1) {
                q.pop_front();
            }
        }

        if (i >= k) {
            res ^= q.front().second;
        }

        x = (a * x + b) % c;
    }

    std::cout << res << "\n";
    return 0;
}