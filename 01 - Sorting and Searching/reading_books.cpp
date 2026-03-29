#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> books;
    std::size_t n, last, sum;

    std::cin >> n;
    books.resize(n);
    
    for (auto& b : books) {
        std::cin >> b;
    }

    std::sort(books.begin(), books.end());

    last = books.back();
    sum = std::accumulate(books.begin(), books.end() - 1, static_cast<std::size_t>(0));

    if (last > sum) {
        std::cout << 2 * last << "\n";
    } else {
        std::cout << sum + last << "\n";
    }

    return 0;
}