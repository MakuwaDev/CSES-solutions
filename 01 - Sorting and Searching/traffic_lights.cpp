#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<std::pair<std::size_t, std::size_t>> intervals;
    std::multiset<std::size_t> lengths;
    std::size_t n, x, l;
    
    std::cin >> x >> n;
    lengths.insert(x);
    intervals.insert({0, x});

    while (n--) {
        std::cin >> l;

        auto it1 = intervals.lower_bound({l, x});
        if (it1 == intervals.begin()) {
            return 1;
        }
        --it1;

        auto i = *it1;
        intervals.erase(it1);

        auto it2 = lengths.find(i.second - i.first);
        if (it2 == lengths.end()) {
            return 1;
        }
        lengths.erase(it2);

        lengths.insert(l - i.first);
        lengths.insert(i.second - l);

        intervals.insert({i.first, l});
        intervals.insert({l, i.second});

        std::cout << *prev(lengths.end()) << " ";
    }

    std::cout << "\n";
    return 0;
}