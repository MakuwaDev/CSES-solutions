#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> len;

    std::size_t n, median, res = 0;
    std::cin >> n;

    len.resize(n);
    for (auto it = len.begin(); it != len.end(); ++it) {
        std::cin >> *it;
    }

    std::nth_element(len.begin(), len.begin() + n / 2, len.end());
    median =  len[n / 2];

    for (auto it = len.begin(); it != len.end(); ++it) {
        if (*it > median) {
            res += *it - median;
        } else {
            res += median - *it;
        }
    }

    std::cout << res << "\n";
    return 0;
}