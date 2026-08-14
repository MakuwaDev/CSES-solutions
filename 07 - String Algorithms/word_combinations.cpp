#include <iostream>
#include <vector>
#include <array>

constexpr std::size_t MOD = 1e9 + 7;

struct Node {
    std::size_t cnt;
    std::array<std::size_t, 26> next;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t k, id;
    std::string s, x;
    std::vector<Node> trie;
    std::vector<std::size_t> dp;

    std::cin >> s;
    std::cin >> k;

    trie.resize(1);
    dp.resize(s.size() + 1);
    dp[s.size()] = 1;

    while (k--) {
        std::cin >> x;
        id = 0;

        for (std::size_t i = 0; i < x.size(); ++i) {
            if (trie[id].next[x[i] - 'a'] != 0) {
                id = trie[id].next[x[i] - 'a'];
            } else {
                trie[id].next[x[i] - 'a'] = trie.size();
                id = trie.size();
                trie.push_back({});
            }
        }

        ++trie[id].cnt;
    }

    for (std::size_t i = s.size() - 1; i < s.size(); --i) {
        id = 0;

        for (std::size_t j = i; j < s.size(); ++j) {
            id = trie[id].next[s[j] - 'a'];

            if (id == 0) {
                break;
            }

            if (trie[id].cnt > 0) {
                dp[i] = (dp[i] + dp[j + 1]) % MOD;
            }
        }
    }

    std::cout << dp[0] << "\n";
    return 0;
}