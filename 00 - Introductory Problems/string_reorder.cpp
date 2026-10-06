#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, prev = 67, next;
    std::string s;
    std::array<std::size_t, 26> cnt;

    std::cin >> s;

    n = s.size();
    std::fill(cnt.begin(), cnt.end(), 0);

    for (auto& c : s) {
        ++cnt[c - 'A'];
    }

    for (auto& c : cnt) {
        if (c > (n + 1) / 2) {
            std::cout << "-1\n";
            return 0;
        }
    }

    while (n > 0) {
        next = 67;

        for (std::size_t i = 0; i < cnt.size(); ++i) {
            if (2 * cnt[i] > n && i != prev) {
                next = i;
                break;
            }
        }

        if (next != 67) {
            std::cout << static_cast<char>(next + 'A');
            --cnt[next];
            prev = next;
            --n;
            continue;
        }

        for (std::size_t i = 0; i < cnt.size(); ++i) {
            if (cnt[i] != 0 && i != prev) {
                std::cout << static_cast<char>(i + 'A');
                --cnt[i];
                prev = i;
                break;
            }
        }

        --n;
    }

    std::cout << "\n";
    return 0;
}