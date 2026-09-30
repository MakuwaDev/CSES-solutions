#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::string s;

    std::cin >> n >> m;

    for (std::size_t r = 0; r < n; ++r) {
        std::cin >> s;

        for (std::size_t c = 0; c < m; ++c) {
            if ((r + c) & 1) {
                std::cout << (s[c] == 'A' ? 'B' : 'A');
            } else {
                std::cout << (s[c] == 'C' ? 'D' : 'C');
            }
        }

        std::cout << "\n";
    }

    return 0;
}