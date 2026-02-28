#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<uint32_t> letter_counts(26);
    std::size_t odd = 0;

    std::string s, res = "";
    std::cin >> s;

    for (auto& c : s) {
        ++letter_counts[c - 'A'];
    }

    for (auto& count : letter_counts) {
        if (count & 1) {
            ++odd;
        }
    }

    if (odd > 1) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    odd = 27;

    for (std::size_t i = 0; i < letter_counts.size(); ++i) {
        if (letter_counts[i] & 1) {
            odd = i;
        }

        for (uint32_t j = 0; j < letter_counts[i] / 2; ++j) {
            res.push_back(i + 'A');
        }
    }

    if (odd < 26) {
        res.push_back(odd + 'A');
    }

    for (std::size_t i = letter_counts.size() - 1; i < letter_counts.size(); --i) {
        for (uint32_t j = 0; j < letter_counts[i] / 2; ++j) {
            res.push_back(i + 'A');
        }
    }

    std::cout << res << "\n";
}