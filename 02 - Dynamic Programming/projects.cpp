#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

struct project {
    std::size_t begin;
    std::size_t end;
    std::size_t value;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<project> projects;
    std::map<std::size_t, std::size_t> dp;
    std::size_t n;

    std::cin >> n;
    projects.resize(n);

    for (auto& p : projects) {
        std::cin >> p.begin >> p.end >> p.value;
    }

    std::sort(projects.begin(), projects.end(), [](project const& a, project const& b) {
        return a.end < b.end;
    });

    dp[0] = 0;

    for (auto const& p : projects) {
        auto it = std::prev(dp.lower_bound(p.begin));
        if (it->second + p.value > dp.rbegin()->second) {
            dp[p.end] = it->second + p.value;
        }
    }

    std::cout << dp.rbegin()->second << "\n";
    return 0;
}