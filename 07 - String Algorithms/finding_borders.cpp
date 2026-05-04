#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> ps;
    std::vector<std::size_t> res;
    std::string s;
    std::size_t n;

    std::cin >> s;
    n = s.size();

    ps.resize(n);

    for (std::size_t i = 1; i < n; ++i) {
        std::size_t j = ps[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = ps[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }

        ps[i] = j;
    }

    --n;

    while (ps[n] > 0) {
        res.push_back(ps[n]);
        n = ps[n] - 1;
    }

    for (auto it = res.rbegin(); it != res.rend(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n";
    return 0;
}