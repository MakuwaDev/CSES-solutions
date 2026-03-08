#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> vec;

    std::size_t n, q, a, b;
    std::cin >> n >> q;

    vec.resize(n + 1);
    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> vec[i];
    }

    std::partial_sum(vec.begin() + 1, vec.end(), vec.begin() + 1);

    while (q--) {
        std::cin >> a >> b;
        std::cout << vec[b] - vec[a - 1] << "\n";
    }

    return 0;
}