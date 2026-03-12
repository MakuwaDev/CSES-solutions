#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> coins;
    std::size_t n, upper = 0;

    std::cin >> n;
    coins.resize(n);

    for (auto& c : coins) {
        std::cin >> c;
    }

    std::sort(coins.begin(), coins.end());

    for (auto const& c : coins) {
        if (c > upper + 1) {
            break;
        } else {
            upper += c;
        }
    }

    std::cout << upper + 1<< "\n";
    return 0;
}