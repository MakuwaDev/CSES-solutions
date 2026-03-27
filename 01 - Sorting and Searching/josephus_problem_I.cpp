#include <iostream>
#include <vector>
#include <numeric>

void josephus(std::vector<std::size_t> const& arr, std::size_t first) {
    if (arr.size() == 1) {
        std::cout << arr[0] << "\n";
        return;
    }

    std::vector<bool> alive(arr.size(), true);
    std::vector<std::size_t> next;

    for (std::size_t i = first; i < arr.size(); i += 2) {
        std::cout << arr[i] << " ";
        alive[i] = false;
    }

    for (std::size_t i = 0; i < arr.size(); ++i) {
        if (alive[i]) {
            next.push_back(arr[i]);
        }
    }

    josephus(next, first == arr.size() % 2 ? 0 : 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::size_t n;

    std::cin >> n;

    arr.resize(n);
    std::iota(arr.begin(), arr.end(), 1);

    josephus(arr, 1);

    return 0;
}