#include <iostream>
#include <cstdint>
#include <vector>
#include <set>
#include <numeric>

constexpr int64_t INF = 1e16 + 16;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> arr;
    std::vector<int64_t> pref;
    std::multiset<int64_t> s;
    std::size_t n, a, b;
    int64_t res = -INF;

    std::cin >> n >> a >> b;

    arr.resize(n + 1);
    pref.resize(n + 1);

    for (auto it = ++arr.begin(); it != arr.end(); ++it) {
        std::cin >> *it;
    }

    std::partial_sum(arr.begin(), arr.end(), pref.begin());

    for (std::size_t i = a; i <= b; ++i) {
        s.insert(pref[i]);
    }

    for (std::size_t i = 1; i <= n - a + 1; ++i) {
        res = std::max(res, *s.rbegin() - pref[i - 1]);
        s.erase(s.find(pref[i + a - 1]));

        if (i + b <= n) {
            s.insert(pref[i + b]);
        }
    }

    std::cout << res << "\n";
    return 0;
}