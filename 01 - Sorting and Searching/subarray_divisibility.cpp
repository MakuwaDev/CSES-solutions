#include <iostream>
#include <cstdint>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> a;
    std::vector<int64_t> psum;
    std::map<int64_t, std::size_t> rev_psum;
    std::size_t res = 0;
    int64_t n, curr = 0;

    std::cin >> n;

    a.resize(n);
    for (auto& x : a) {
        std::cin >> x;
    }

    for (std::size_t i = 0; i < static_cast<std::size_t>(n); ++i) {
        curr = (curr + a[i]) % n;
        if (curr < 0) {
            curr += n;
        }

        if (curr == 0) {
            ++res;
        }
        
        res += rev_psum[curr];

        ++rev_psum[curr];
    }

    std::cout << res << "\n";
    return 0;
}