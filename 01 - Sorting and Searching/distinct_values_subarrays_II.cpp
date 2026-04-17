#include <iostream>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> arr;
    std::map<std::size_t, std::size_t> elements;
    std::size_t n, k, res = 0, i = 0, x;

    std::cin >> n >> k;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    for (std::size_t j = 0; j < n; ++j) {
        if (elements.contains(arr[j])) {
            ++elements[arr[j]];
        } else {
            elements[arr[j]] = 1;
        }

        while (elements.size() > k) {
            x = arr[i++];

            if (!(--elements[x])) {
                elements.erase(x);
            }
        }

        res += (j - i + 1);
    }

    std::cout << res << "\n";
    return 0;
}