#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

std::vector<std::size_t> z(std::string const& s) {
    std::size_t n = s.size(), l = 0, r = 0;
    std::vector<std::size_t> z(n);

    for (std::size_t i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = std::min(r - i, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    auto v = z(s);

    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i + v[i] == s.size()) {
            std::cout << i << " ";
        }
    }

    std::cout << s.size() << "\n";
    return 0;
}