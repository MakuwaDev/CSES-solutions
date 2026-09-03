#include <iostream>
#include <vector>

std::vector<std::string> forest;
std::vector<std::vector<std::size_t>> bit;

void update(std::size_t x, std::size_t y, std::size_t val) {
    for (std::size_t i = x; i < bit.size(); i += i & -i) {
        for (std::size_t j = y; j < bit.size(); j += j & -j) {
            bit[i][j] += val;
        }
    }
}

std::size_t prefix(std::size_t x, std::size_t y) {
    std::size_t res = 0;

    for (std::size_t i = x; i > 0; i -= i & -i) {
        for (std::size_t j = y; j > 0; j -= j & -j) {
            res += bit[i][j];
        }
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, q, x1, y1, x2, y2, res;
    std::string row;
    char t;

    std::cin >> n >> q;

    bit.assign(n + 1, std::vector<std::size_t>(n + 1, 0));
    forest.assign(n + 1, ""); 

    for (std::size_t i = 1; i <= n; ++i) {
        std::string row;
        std::cin >> row;
        forest[i] = " " + row;

        for (std::size_t j = 1; j <= n; ++j) {
            if (forest[i][j] == '*') {
                update(i, j, 1);
            }
        }
    }

    while (q--) {
        std::cin >> t >> x1 >> y1;

        if (t == '1') {
            if (forest[x1][y1] == '*') {
                update(x1, y1, -1);
                forest[x1][y1] = '.';
            } else {
                update(x1, y1, 1);
                forest[x1][y1] = '*';
            }
        } else {
            std::cin >> x2 >> y2;

            res = prefix(x2, y2) 
                - prefix(x1 - 1, y2)
                - prefix(x2, y1 - 1)
                + prefix(x1 - 1, y1 - 1);
            
            std::cout << res << "\n";
        }
    }

    return 0;
}