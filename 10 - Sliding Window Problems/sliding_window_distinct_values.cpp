#include <iostream>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k;
    std::vector<std::size_t> arr;
    std::map<std::size_t, std::size_t> cnt;

    std::cin >> n >> k;

    arr.resize(n);
    for (auto& x : arr) {
        std::cin >> x;
    }

    for (std::size_t i = 0; i < n; ++i) {
        auto res = cnt.insert({arr[i], 1});
        if (!res.second) {
            ++(res.first->second);
        }

        if (i >= k - 1) {
            if (i >= k) {
                --cnt[arr[i - k]];

                if (!cnt[arr[i - k]]) {
                    cnt.erase(arr[i - k]);
                }
            }

            std::cout << cnt.size() << " ";
        }
    }

    std::cout << "\n";
    return 0;
}