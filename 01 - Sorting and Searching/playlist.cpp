#include <iostream>
#include <vector>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> v;
    std::set<std::size_t> s;

    std::size_t n, res = 0, i, j;
    std::cin >> n;

    v.resize(n);
    for (auto& x : v) {
        std::cin >> x;
    }

    i = j = 0;

    while (j < n) {
        while (j < n && !s.contains(v[j])) {
            s.insert(v[j++]);
        }

        res = std::max(res, j - i);

        if (j < n) {
            while (v[i] != v[j]) {
                s.erase(v[i++]);
            }

            s.erase(v[i++]);
            s.insert(v[j++]);
        }
    }

    std::cout << res << "\n";
    return 0;
}