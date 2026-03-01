#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int32_t> applicants;
    std::vector<int32_t> apartments;

    std::size_t n, m,res = 0;
    int32_t k;
    std::cin >> n >> m >> k;

    applicants.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> applicants[i];
    }

    apartments.resize(m);
    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> apartments[i];
    }

    std::sort(applicants.begin(), applicants.end());
    std::sort(apartments.begin(), apartments.end());

    std::size_t j = 0;
    for (std::size_t i = 0; i < n; ++i) {
        while (j < m && applicants[i] > apartments[j] + k) {
            ++j;
        }

        if (j < m && applicants[i] + k >= apartments[j]) {
            ++res;
            ++j;
        }
    }

    std::cout << res << "\n";
    return 0;
}