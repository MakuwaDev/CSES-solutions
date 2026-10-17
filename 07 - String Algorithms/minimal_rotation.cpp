#include <iostream>
#include <string>

std::string minrot(std::string const& s) {
    std::size_t n = s.size(), i = 0, j = 1, k = 0;
    std::string ss = s + s;

    while (i < n && j < n && k < n) {
        if (ss[i + k] == ss[j + k]) {
            ++k;
            continue;
        }

        if (ss[i + k] > ss[j + k]) {
            i = i + k + 1;
        } else {
            j = j + k + 1;
        }

        if (i == j) {
            ++j;
        }

        k = 0;
    }

    return ss.substr(std::min(i, j), n);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    std::cout << minrot(s) << "\n";
    return 0;
}