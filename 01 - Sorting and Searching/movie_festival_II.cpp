#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, std::size_t>> intervals;
    std::multiset<std::size_t, std::greater<>> agents;
    std::size_t n, k, res = 0;

    std::cin >> n >> k;

    intervals.resize(n);
    for (auto& i : intervals) {
        std::cin >> i.first >> i.second;
    }

    std::sort(intervals.begin(), intervals.end(), [](auto const& a, auto const& b) {
        return a.second < b.second;
    });

    std::fill_n(std::inserter(agents, agents.end()), k, 0);

    for (auto const& i : intervals) {
        auto it = agents.lower_bound(i.first);

        if (it != agents.end()) {
            ++res;

            agents.erase(it);
            agents.insert(i.second);
        }
    }

    std::cout << res << "\n";
    return 0;
}