#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, std::size_t>> v;
    std::size_t n, sum, x, j, k;
    
    std::cin >> n >> sum;

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> x;
        v.push_back({x, i});
    }

    std::sort(v.begin(), v.end());

    for (std::size_t i = 0; i < n; ++i) {
        if (v[i].first >= sum) {
            continue;
        }

        j = 0;
        k = n - 1;

        while (j < k) {
            x = v[i].first + v[j].first + v[k].first;
            if (x < sum || j == i) {
                ++j;
            } else if (x > sum || k == i) {
                --k;
            } else {
                std::cout << v[i].second + 1 << " " << v[j].second + 1 << " " << v[k].second + 1 << "\n";
                return 0;
            }
        }
    }

    std::cout << "IMPOSSIBLE\n";
    return 0;
}