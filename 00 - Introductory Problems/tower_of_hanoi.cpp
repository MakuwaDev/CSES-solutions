#include <iostream>
#include <vector>
#include <cstdint>

void hanoi(std::vector<std::pair<uint32_t, uint32_t>>& moves, uint32_t n, uint32_t a, uint32_t b, uint32_t c) {
    if (n) {
        hanoi(moves, n - 1, a, c, b);
        moves.push_back({a, c});
        hanoi(moves, n - 1, b, a, c);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n;
    std::cin >> n;

    std::vector<std::pair<uint32_t, uint32_t>> moves;

    hanoi(moves, n, 1, 2, 3);

    std::cout << moves.size() << "\n";
    for (auto& m : moves) {
        std::cout << m.first << " " << m.second << "\n";
    }

    std::cout << "\n";
}