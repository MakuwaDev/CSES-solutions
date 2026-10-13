#include <iostream>
#include <string>
#include <array>

std::size_t map(char c) {
    switch (c) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
    }

    return -1;
}

char rev_map(std::size_t x) {
    switch (x) {
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'G';
        case 3:
            return 'T';
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, res = "";
    std::array<bool, 4> seen{false, false, false, false};
    bool add;

    std::cin >> s;

    for (auto const& c : s) {
        add = true;
        seen[map(c)] = true;

        for (auto const& b : seen) {
            add &= b;
        }

        if (add) {
            res.push_back(c);
            for (auto& b : seen) {
                b = false;
            }
        }
    }

    for (std::size_t i = 0; i < seen.size(); ++i) {
        if (!seen[i]) {
            res.push_back(rev_map(i));
            break;
        }
    }

    std::cout << res << "\n";
    return 0;
}