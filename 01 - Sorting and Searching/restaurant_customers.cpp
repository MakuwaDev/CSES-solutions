#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, bool>> events;

    std::size_t n, res = 0, curr = 0, a, b;
    std::cin >> n;
    
    events.reserve(2 * n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a >> b;
        events.push_back({a, 0});
        events.push_back({b, 1});
    }

    std::sort(events.begin(), events.end());

    for (auto& e: events) {
        if (e.second) {
            --curr;
        } else {
            ++curr;
            res = std::max(curr, res);
        }
    }

    std::cout << res << "\n";
    return 0;
}