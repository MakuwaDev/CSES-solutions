#include <iostream>
#include <vector>
#include <numeric>

struct QueryInfo {
    std::size_t other;
    std::size_t id;
};

std::size_t UNREACHABLE;

std::vector<std::size_t> rep;
std::vector<std::vector<QueryInfo>> query_vec;
std::vector<std::size_t> res;

std::size_t dsu_find(std::size_t x) {
    if (rep[x] == x) {
        return x;
    }

    return rep[x] = dsu_find(rep[x]);
}

void dsu_union(std::size_t x, std::size_t y, std::size_t day) {
    if (dsu_find(x) != dsu_find(y)) {
        x = dsu_find(x);
        y = dsu_find(y);

        if (query_vec[y].size() > query_vec[x].size()) {
            std::swap(x, y);
        }

        rep[y] = x;

        for (auto const& item : query_vec[y]) {
            if (res[item.id] != UNREACHABLE) {
                continue;
            }

            if (dsu_find(item.other) == x) {
                res[item.id] = day + 1;
            } else {
                query_vec[x].push_back(item);
            }
        }

        query_vec[y].clear();
        query_vec[y].shrink_to_fit();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, q, a, b;
    std::vector<std::pair<std::size_t, std::size_t>> roads;
    std::vector<std::pair<std::size_t, std::size_t>> queries;

    std::cin >> n >> m >> q;

    rep.resize(n);
    query_vec.resize(n);
    res.resize(q);
    roads.resize(m);
    queries.resize(q);

    UNREACHABLE = m + 5;

    std::iota(rep.begin(), rep.end(), 0);
    std::fill(res.begin(), res.end(), UNREACHABLE);

    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        --a; --b;
        roads[i] = {a, b};
    }

    for (std::size_t i = 0; i < q; ++i) {
        std::cin >> a >> b;
        --a; --b;

        if (a != b) {
            query_vec[a].push_back({b, i});
            query_vec[b].push_back({a, i});
        } else {
            res[i] = 0;
        }
    }

    for (std::size_t i = 0; i < m; ++i) {
        dsu_union(roads[i].first, roads[i].second, i);
    }

    for (auto const& r : res) {
        if (r != UNREACHABLE) {
            std::cout << r << "\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}