#include <iostream>
#include <vector>
#include <algorithm>

using movie = std::pair<std::size_t, std::size_t>;

bool ends_earlier(movie const& a, movie const& b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }

    return a.first < b.first;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<movie> movies;

    std::size_t n, res = 0;
    std::cin >> n;

    movies.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> movies[i].first >> movies[i].second;
    }

    std::sort(movies.begin(), movies.end(), ends_earlier);

    movie curr = {0, 0};

    for (auto& m : movies) {
        if (m.first >= curr.second) {
            curr = m;
            ++res;
        }
    }

    std::cout << res << "\n";
}