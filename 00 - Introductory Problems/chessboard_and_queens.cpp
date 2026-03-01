#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

std::vector<std::vector<bool>> covered(8);
std::vector<bool> usedCol(8);
std::vector<bool> diag1(15); // i + j
std::vector<bool> diag2(15); // i - j
uint32_t res = 0;

void backtrack(std::size_t row) {
    if (row == 8) {
        ++res;
        return;
    }

    for (std::size_t col = 0; col < 8; ++col) {
        if (!covered[row][col] && !usedCol[col] && !diag1[row + col] && !diag2[row - col + 7]) {
            usedCol[col] = diag1[row + col] = diag2[row - col + 7] = true;
            backtrack(row + 1);
            usedCol[col] = diag1[row + col] = diag2[row - col + 7] = false;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (auto& vec : covered) {
        std::string s;
        std::cin >> s;

        vec.resize(8);
        for (std::size_t i = 0; i < 8; ++i) {
            if (s[i] == '*') {
                vec[i] = true;
            }
        }
    }

    backtrack(0);

    std::cout << res << "\n";
    return 0;
}