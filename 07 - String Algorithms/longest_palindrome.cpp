#include <iostream>
#include <vector>

std::vector<std::size_t> manacher_odd(std::string s) {
    std::size_t n = s.size(), l = 0, r = 1;
    std::vector<std::size_t> p(n + 2);

    s = "$" + s + "^";

    for (std::size_t i = 1; i <= n; ++i) {
        if (i <= r) {
            p[i] = std::min(r - i, p[l + r - i]);
        }

        while (s[i - p[i]] == s[i + p[i]]) {
            ++p[i];
        }

        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }

    return std::vector<std::size_t>(std::begin(p) + 1, std::end(p) - 1);
}

std::vector<std::size_t> manacher(std::string const& s) {
    std::string t;

    for (auto const& c: s) {
        t += std::string("#") + c;
    }

    auto res = manacher_odd(t + "#");

    return std::vector<std::size_t>(std::begin(res) + 1, std::end(res) - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::size_t len = 0, id = 0;

    std::cin >> s;

    if (!s.empty()) {
        auto radius = manacher(s);

        for (std::size_t i = 0; i < radius.size(); ++i) {
            if (radius[i] - 1 > len) {
                len = radius[i] - 1;
                id = i;
            }
        }

        std::cout << s.substr((id - len + 1) / 2, len);
    }

    std::cout << "\n";
    return 0;
}