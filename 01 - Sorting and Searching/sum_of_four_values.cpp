#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, std::size_t>> a;
    std::size_t n, sum, x;

    std::cin >> n >> sum;
    a.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i + 1;
    }

    if (n < 4) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::sort(a.begin(), a.end());

    for (std::size_t i = 0; i < n - 3; ++i) {
        for (std::size_t j = i + 3; j < n; ++j) {
            std::size_t k = i + 1, l = j - 1;

            if (a[i].first + a[j].first > sum) {
                break;
            }

            while (k < l) {
                x = a[i].first + a[j].first + a[k].first + a[l].first;

                if (x < sum) {
                    ++k;
                } else if (x > sum) {
                    --l;
                } else {
                    std::cout << a[i].second << " " << a[j].second << " " << a[k].second << " " << a[l].second << "\n";
                    return 0;
                }
            }
        }
    }

    std::cout << "IMPOSSIBLE\n";
    return 0;
}