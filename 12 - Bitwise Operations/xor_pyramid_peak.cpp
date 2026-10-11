#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, res = 0;
    std::vector<std::size_t> arr;

    std::cin >> n;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    for (std::size_t i = 0; i < n; ++i) {
        if ((i & (n - 1)) == i) {
            res ^= arr[i];
        }
    }

    std::cout << res << "\n";
    return 0;
}