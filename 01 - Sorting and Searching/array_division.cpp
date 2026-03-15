#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k, max_elem = 0, sum = 0;
    std::vector<std::size_t> arr;

    std::cin >> n >> k;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
        max_elem = std::max(max_elem, x);
        sum += x;
    }
    
    auto range = std::ranges::iota_view(max_elem, sum);
    auto it = std::ranges::lower_bound(range, true, {}, [&](std::size_t max_sum) {
        std::size_t curr = 0, subs = 1;

        for (std::size_t i = 0; i < n; ++i) {
            if (curr + arr[i] <= max_sum) {
                curr += arr[i];
            } else {
                ++subs;
                curr = arr[i];
            }
        }

        return subs <= k;
    });

    std::cout << *it << "\n";
    return 0;
}