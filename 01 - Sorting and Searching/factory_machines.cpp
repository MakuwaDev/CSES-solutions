#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> machines;
    std::size_t n, t, low, top;

    std::cin >> n >> t;
    machines.resize(n);

    for (auto& m : machines) {
        std::cin >> m;
    }

    std::sort(machines.begin(), machines.end());

    auto check = [&](std::size_t x) {
        std::size_t sum = 0;

        for (auto const& m : machines) {
            sum += x / m;
        }

        return sum >= t;
    };

    low = 0;
    top = t * machines.back() / n + 10;
    auto range = std::ranges::iota_view(low, top);

    auto it = std::ranges::lower_bound(range, true, {}, [&](std::size_t x) {
        return check(x);
    });

    std::cout << *it << "\n";
    return 0;
}