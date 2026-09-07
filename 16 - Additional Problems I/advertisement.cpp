#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, res = 0;
    std::vector<std::size_t> arr;
    std::vector<std::size_t> stack;

    std::cin >> n;
    arr.resize(n);

    for (auto& x : arr) {
        std::cin >> x;
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (stack.empty() || arr[i] >= arr[stack.back()]) {
            stack.push_back(i);
        } else {
            while (!stack.empty() && arr[i] < arr[stack.back()]) {
                std::size_t j = stack.back();
                stack.pop_back();

                std::size_t w = stack.empty() ? i : i - stack.back() - 1;
                res = std::max(res, arr[j] * w);
            }

            stack.push_back(i);
        }
    }

    while (!stack.empty()) {
        std::size_t j = stack.back();
        stack.pop_back();

        std::size_t w = stack.empty() ? n : n - stack.back() - 1;
        res = std::max(res, arr[j] * w);
    }

    std::cout << res << "\n";
    return 0;
}