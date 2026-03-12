#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> a;

    std::size_t n, sum, curr, res = 0, i, j;
    std::cin >> n >> sum;

    a.resize(n);
    for (auto& x : a) {
        std::cin >> x;
    }

    curr = res = i = j = 0;
    curr = 0;

    for (; j < n; ++j) {
        curr += a[j];

        while (curr > sum) {
            curr -= a[i++];
        }

        if (curr == sum) {
            ++res;
        }
    }

    std::cout << res << "\n";
    return 0;
}