#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<std::size_t, std::size_t>> stack;
    std::size_t n, x;

    std::cin >> n;

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> x;

        while (!stack.empty() && stack.back().first >= x) {
            stack.pop_back();
        }

        if (stack.empty()) {
            std::cout << "0 ";
        } else {
            std::cout << stack.back().second << " ";
        }

        stack.push_back({x, i});
    }

    std::cout << "\n";
    return 0;
}