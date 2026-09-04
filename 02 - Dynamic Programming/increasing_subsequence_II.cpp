#include <iostream>
#include <vector>
#include <algorithm>

constexpr std::size_t MOD = 1e9 + 7;

std::size_t n;
std::vector<std::size_t> bit;

void add(std::size_t i, std::size_t val) {
    for (; i < bit.size(); i += i & -i) {
        bit[i] = (bit[i] + val) % MOD;
    }
}

std::size_t sum(std::size_t i) {
    std::size_t res = 0;

    for (; i > 0; i -= i & -i) {
        res = (res + bit[i]) % MOD;
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t id = 0, count;
    std::vector<std::size_t> arr;
    std::vector<std::size_t> scale;

    std::cin >> n;

    arr.resize(n);
    scale.reserve(n);

    for (auto& x : arr) {
        std::cin >> x;
        scale.push_back(x);
    }

    std::sort(scale.begin(), scale.end());
    scale.erase(std::unique(scale.begin(), scale.end()), scale.end());
    bit.resize(scale.size() + 1, 0);

    auto get_scale = [&](std::size_t x) {
        return std::lower_bound(scale.begin(), scale.end(), x) - scale.begin() + 1;
    };

    for (std::size_t i = 0; i < n; ++i) {
        id = get_scale(arr[i]);
        count = (sum(id - 1) + 1) % MOD;
        add(id, count);
    }

    std::cout << sum(scale.size()) << "\n";
    return 0;
}