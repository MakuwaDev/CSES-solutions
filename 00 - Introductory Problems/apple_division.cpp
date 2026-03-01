#include <iostream>
#include <cstdint>
#include <vector>
#include <numeric>
#include <cmath>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    std::vector<int64_t> weights;
 
    int64_t n, min_diff, sum;
    std::cin >> n;
    weights.resize(n);
 
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
 
    sum = min_diff = std::accumulate(weights.begin(), weights.end(), 0LL);
 
    for (int64_t mask = 0; mask < (1LL << n); ++mask) {
        int64_t taken = 0;
 
        for (int64_t i = 0; i < n; ++i) {
            if (mask & (1LL << i)) {
                taken += weights[i];
            }
        }
 
        min_diff = std::min(min_diff, static_cast<int64_t>(std::llabs(sum - 2 * taken)));
    }
 
    std::cout << min_diff << "\n";
    return 0;
}