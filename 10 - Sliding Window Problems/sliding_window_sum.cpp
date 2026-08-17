#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, k;
    int64_t x, a, b, c, res = 0, sum = 0, head, tail;

    std::cin >> n >> k;
    std::cin >> x >> a >> b >> c;

    head = tail = x;

    for (std::size_t i = 1; i <= n; ++i) {
        sum += head;
        head = (a * head + b) % c;

        if (i >= k) {
            res = res ^ sum;
            sum -= tail;
            tail = (a * tail + b) % c;
        }
    }

    std::cout << res << "\n";
    return 0;
}