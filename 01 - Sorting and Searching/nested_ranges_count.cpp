#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<
    std::pair<std::size_t, std::size_t>,
    null_type,
    std::less<std::pair<std::size_t, std::size_t>>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_multiset;

struct range {
    std::size_t l;
    std::size_t r;
    std::size_t i;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<range> ranges;
    std::vector<std::size_t> contains;
    std::vector<std::size_t> contained;
    ordered_multiset oms;
    std::size_t n, id = 0;
    
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

    for (std::size_t i = 0; i < n; ++i) {
        contained[ranges[i].i] = oms.size() - oms.order_of_key({ranges[i].r, 0});
        oms.insert({ranges[i].r, id++});
    }

    id = 0;
    oms.clear();

    for (std::size_t i = n - 1; i < n; --i) {
        contains[ranges[i].i] = oms.order_of_key({ranges[i].r, n + 1});
        oms.insert({ranges[i].r, id++});
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