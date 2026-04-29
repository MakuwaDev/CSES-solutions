#include <iostream>
#include <vector>
#include <set>

std::vector<std::size_t> xs;

std::multiset<std::size_t> low;
std::multiset<std::size_t> up;

std::size_t low_sum;
std::size_t up_sum;

std::size_t n, k;

void insert(std::size_t x) {
    std::size_t m = *low.rbegin();

    if (x > m) {
        up.insert(x);
        up_sum += x;

        if (up.size() > k / 2) {
            auto y = up.begin();

            low_sum += *y;
            up_sum -= *y;

            low.insert(*y);
            up.erase(y);
        }
    } else {
        low.insert(x);
        low_sum += x;

        if (low.size() > (k + 1) / 2) {
            auto y = low.rbegin();

            up_sum += *y;
            low_sum -= *y;

            up.insert(*low.rbegin());
            low.erase(--low.end());
        }
    }
}

void erase(std::size_t x) {
    if (up.find(x) != up.end()) {
        up.erase(up.find(x));
        up_sum -= x;
    } else {
        low.erase(low.find(x));
        low_sum -= x;
    }

    if (low.empty()) {
        auto y = up.begin();

        low_sum += *y;
        up_sum -= *y;

        low.insert(*y);
        up.erase(y);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;

    xs.resize(n);
    for (auto& x : xs) {
        std::cin >> x;
    }

    low.insert(xs.front());
    low_sum += xs.front();

    for (std::size_t i = 1; i < k; ++i) {
        insert(xs[i]);
    }

    auto med = *low.rbegin();
    std::cout << low.size() * med - low_sum + up_sum - med * up.size() << "\n";

    for (std::size_t i = k; i < n; ++i) {
        if (k == 1) {
            insert(xs[i]);
            erase(xs[i - 1]);
        } else {
            erase(xs[i - k]);
            insert(xs[i]);
        }
        
        auto med = *low.rbegin();
        std::cout << low.size() * med - low_sum + up_sum - med * up.size() << " ";
    }

    std::cout << "\n";
    return 0;
}