#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> ps;
    std::string t, p, s;
    std::size_t res = 0;

    std::cin >> t >> p;

    s = p + '#' + t;
    ps.resize(s.size());

    for (std::size_t i = 1; i < s.size(); ++i) {
        std::size_t j = ps[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = ps[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }

        ps[i] = j;
    }

    for (auto const& x : ps) {
        res += (x == p.size());
    }

    std::cout << res << "\n";
    return 0;
}