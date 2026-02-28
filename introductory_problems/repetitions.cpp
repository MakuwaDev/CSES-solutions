#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t currLen = 0, maxLen = 0;

    std::string s;
    std::cin >> s;

    if (s.empty()) {
        std::cout << "0\n";
        return 0;
    }

    currLen = maxLen = 1;
    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            currLen += 1;
        } else {
            maxLen = std::max(maxLen, currLen);
            currLen = 1;
        }
    }

    std::cout << std::max(maxLen, currLen) << "\n";

    return 0;
}
