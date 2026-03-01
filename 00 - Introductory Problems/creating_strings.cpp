#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<std::string> permutations;

    std::string s;
    std::cin >> s;

    std::sort(s.begin(), s.end());

    do {
        permutations.insert(s);
    } while (std::next_permutation(s.begin(), s.end()));

    std::cout << permutations.size() << "\n";
    for (auto& p : permutations) {
        std::cout << p << "\n";
    }
}