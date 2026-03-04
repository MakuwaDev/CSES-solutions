#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, std::size_t>> a;

    std::size_t n, x, i, j, sum;
    std::cin >> n >> x;

    a.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }

    std::sort(a.begin(), a.end(),
              [](auto const& a, auto const& b) {
        return a.first < b.first;
    });

    i = 0;
    j = n - 1;

    while (i < j) {
        sum = a[i].first + a[j].first;
        if (sum > x) {
            --j;
        } else if (sum < x) {
            ++i;
        } else {
            std::cout << a[i].second + 1 << " " << a[j].second + 1 << "\n";
            return 0;
        }
    }

    std::cout << "IMPOSSIBLE\n";
    return 0;
}