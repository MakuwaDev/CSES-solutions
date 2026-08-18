#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    int64_t res = 0;
    std::vector<std::pair<int64_t, int64_t>> vertices;

    std::cin >> n;
    vertices.resize(n);

    for (auto& [x, y] : vertices) {
        std::cin >> x >> y;
    }

    vertices.push_back(vertices.front());

    for (std::size_t i = 1; i < vertices.size(); ++i) {
        res += (vertices[i - 1].first * vertices[i].second - vertices[i].first * vertices[i - 1].second);
    }

    std::cout << (res < 0 ? -res : res) << "\n";
    return 0;
}