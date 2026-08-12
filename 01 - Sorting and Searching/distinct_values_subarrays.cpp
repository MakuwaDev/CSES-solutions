#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, res = 0, l = 0, r = 0;
    std::vector<std::size_t> t;
    std::unordered_set<std::size_t> s;

    std::cin >> n;
    t.resize(n);

    for (auto& x : t) {
        std::cin >> x;
    }

    for (; r < n; ++r) {
        while (s.contains(t[r])) {
            s.erase(t[l++]);
        }

        s.insert(t[r]);
        res += (r - l + 1);
    }

    std::cout << res << "\n";
    return 0;
}