#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

std::vector<int64_t> subset_sum(std::vector<int64_t> const& arr, std::size_t l, std::size_t r) {
    std::vector<int64_t> res;
    std::size_t len = r - l + 1;

    for (int32_t mask = 0; mask < (1 << len); ++mask) {
        int64_t sum = 0;

        for (std::size_t i = 0; i < len; ++i) {
            if (mask & (1 << i)) {
                sum += arr[l + i];
            }
        }

        res.push_back(sum);
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> arr, l, r;
    std::size_t n, res = 0;
    int64_t x;

    std::cin >> n >> x;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    l = subset_sum(arr, 0, n / 2 - 1);
    r = subset_sum(arr, n / 2, n - 1);

    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());

    for (auto const& y : l) {
        auto first = std::lower_bound(r.begin(), r.end(), x - y);
        auto last = std::upper_bound(r.begin(), r.end(), x - y);

        res += (last - first);
    }

    std::cout << res << "\n";
    return 0;
}