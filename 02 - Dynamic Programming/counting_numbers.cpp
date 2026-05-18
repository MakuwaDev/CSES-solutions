#include <iostream>
#include <cstring>
#include <cstdint>

int64_t dp[20][10][2][2];

int64_t calc(std::string const& num, int64_t n, int64_t x, bool lz, bool tight) {
    int64_t res = 0, ub;

    if (!n) {
        return 1;
    }

    if (x != -1 && dp[n][x][lz][tight] != -1) {
        return dp[n][x][lz][tight];
    }

    ub = tight ? (num[num.size() - n] - '0') : 9;
    for (int64_t dig = 0; dig <= ub; ++dig) {
        if (dig == x && !lz) {
            continue;
        }

        res += calc(num, n - 1, dig, (lz && !dig), tight && (dig == ub));
    }

    return dp[n][x][lz][tight] = res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t a, b;
    std::string sa, sb;

    std::cin >> a >> b;

    sa = std::to_string(a - 1);
    sb = std::to_string(b);

    std::memset(dp, -1, sizeof(dp));
    a = calc(sa, sa.size(), -1, 1, 1);

    std::memset(dp, -1, sizeof(dp));
    b = calc(sb, sb.size(), -1, 1, 1);

    std::cout << b - a << "\n";
    return 0;
}