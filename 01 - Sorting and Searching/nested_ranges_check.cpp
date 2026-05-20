#include <iostream>
#include <vector>
#include <algorithm>

struct range {
    std::size_t l;
    std::size_t r;
    std::size_t i;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<range> ranges;
    std::vector<bool> contains;
    std::vector<bool> contained;
    std::size_t n, r;
    
    std::cin >> n;

    ranges.resize(n);
    contains.resize(n);
    contained.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> ranges[i].l >> ranges[i].r;
        ranges[i].i = i;
    }

    std::sort(ranges.begin(), ranges.end(), [](auto const& a, auto const& b) {
        return a.l != b.l ? a.l < b.l : a.r > b.r;
    });

    r = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (r >= ranges[i].r) {
            contained[ranges[i].i] = true;
        }

        r = std::max(r, ranges[i].r);
    }

    r = 1e9 + 9;
    for (std::size_t i = n - 1; i < n; --i) {
        if (r <= ranges[i].r) {
            contains[ranges[i].i] = true;
        }

        r = std::min(r, ranges[i].r);
    }

    for (auto const& x : contains) {
        std::cout << x << " ";
    }

    std::cout << "\n";
    for (auto const& x : contained) {
        std::cout << x << " ";
    }

    std::cout << "\n";
    return 0;
}