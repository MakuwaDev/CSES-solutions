#include <iostream>
#include <vector>
#include <limits>

constexpr std::size_t INF = std::numeric_limits<std::size_t>::max();

std::vector<std::vector<std::size_t>> dag;
std::vector<std::size_t> dp;

std::size_t dfs(std::size_t v) {
    if (dp[v] != 0) {
        return dp[v];
    }

    std::size_t res = 0;

    for (auto& u : dag[v]) {
        res = std::max(res, dfs(u));
    }

    return dp[v] = res + 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, highest = 0;
    std::vector<std::size_t> arr;
    std::vector<std::size_t> stack;
    std::vector<std::size_t> lwall, rwall;

    std::cin >> n;

    arr.resize(n);
    dag.resize(n + 1);
    dp.resize(n + 1, 0);
    lwall.resize(n);
    rwall.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (arr[i] > highest) {
            highest = arr[i];
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        while (!stack.empty() && arr[stack.back()] <= arr[i]) {
            stack.pop_back();
        }

        lwall[i] = stack.empty() ? INF : stack.back();
        stack.push_back(i);
    }

    stack.clear();
    for (std::size_t i = n - 1; i < n; --i) {
        while (!stack.empty() && arr[stack.back()] <= arr[i]) {
            stack.pop_back();
        }

        rwall[i] = stack.empty() ? INF : stack.back();
        stack.push_back(i);
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (lwall[i] != INF && rwall[i] != INF) {
            if (arr[lwall[i]] <= arr[rwall[i]]) {
                dag[lwall[i] + 1].push_back(i + 1);
            }

            if (arr[rwall[i]] <= arr[lwall[i]]) {
                dag[rwall[i] + 1].push_back(i + 1);
            }
        } else {
            if (lwall[i] != INF) {
                dag[lwall[i] + 1].push_back(i + 1);
            }

            if (rwall[i] != INF) {
                dag[rwall[i] + 1].push_back(i + 1);
            }
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (arr[i] == highest) {
            dag[0].push_back(i + 1);
        }
    }

    std::cout << dfs(0) - 1 << "\n";
    return 0;
}