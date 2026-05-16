#include <iostream>
#include <vector>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::vector<std::size_t> pos;
    std::set<std::pair<std::size_t, std::size_t>> pairs;
    std::size_t n, q, res = 1, a, b;

    std::cin >> n >> q;

    arr.resize(n + 1);
    pos.resize(n + 1);

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        pos[arr[i]] = i;
    }

    for (std::size_t i = 1; i < n; ++i) {
        res += (pos[i] > pos[i + 1]);
    }

    while (q--) {
        std::cin >> a >> b;

        if (arr[a] < n) {
            pairs.insert({arr[a], arr[a] + 1});
        }

        if (arr[a] > 1) {
            pairs.insert({arr[a] - 1, arr[a]});
        }

        if (arr[b] < n) {
            pairs.insert({arr[b], arr[b] + 1});
        }

        if (arr[b] > 1) {
            pairs.insert({arr[b] - 1, arr[b]});
        }

        for (auto const& p : pairs) {
            res -= (pos[p.first] > pos[p.second]);
        }

        std::swap(arr[a], arr[b]);
        pos[arr[a]] = a;
        pos[arr[b]] = b;

        for (auto const& p : pairs) {
            res += (pos[p.first] > pos[p.second]);
        }

        pairs.clear();
        std::cout << res << "\n";
    }

    return 0;
}