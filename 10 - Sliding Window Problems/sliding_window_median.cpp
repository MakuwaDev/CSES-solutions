#include <iostream>
#include <vector>
#include <set>

std::vector<std::size_t> xs;
std::multiset<std::size_t> low;
std::multiset<std::size_t> up;
std::size_t n, k;

void insert(std::size_t x) {
    std::size_t m = *low.rbegin();

    if (x > m) {
        up.insert(x);

        if (up.size() > k / 2) {
            low.insert(*up.begin());
            up.erase(up.begin());
        }
    } else {
        low.insert(x);

        if (low.size() > (k + 1) / 2) {
            up.insert(*low.rbegin());
            low.erase(--low.end());
        }
    }
}

void erase(std::size_t x) {
    if (up.find(x) != up.end()) {
        up.erase(up.find(x));
    } else {
        low.erase(low.find(x));
    }

    if (low.empty()) {
        low.insert(*up.begin());
        up.erase(up.begin());
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
    for (std::size_t i = 1; i < k; ++i) {
        insert(xs[i]);
    }

    std::cout << *low.rbegin() << " ";

    for (std::size_t i = k; i < n; ++i) {
        if (k == 1) {
            insert(xs[i]);
            erase(xs[i - 1]);
        } else {
            erase(xs[i - k]);
            insert(xs[i]);
        }

        std::cout << *low.rbegin() << " ";
    }

    std::cout << "\n";
    return 0;
}