#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t x, y, n, res = 0;
    std::multiset<std::size_t> sticks;

    std::cin >> x >> n;

    while (n--) {
        std::cin >> x;
        sticks.insert(x);
    }

    while (sticks.size() > 1) {
        x = *sticks.begin();
        sticks.erase(sticks.begin());

        y = *sticks.begin();
        sticks.erase(sticks.begin());

        res += x + y;
        sticks.insert(x + y);
    }

    std::cout << res << "\n";
    return 0;
}