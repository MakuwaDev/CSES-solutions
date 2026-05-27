#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>

struct Query {
    std::size_t l;
    std::size_t r;
    std::size_t id;

    bool operator<(Query const& other) const {
        return r < other.r;
    }
};

class FenwickTree {
public:
    FenwickTree(std::size_t n) : n(n), tree(n + 1, 0) {}

    void update(std::size_t i, int32_t delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    int32_t query(std::size_t l, std::size_t r) {
        return query(r) - query(l - 1);
    }

private:
    std::size_t n;
    std::vector<int32_t> tree;

    int32_t query(std::size_t i) {
        int32_t sum = 0;

        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }

        return sum;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::size_t> arr;
    std::vector<Query> queries;
    std::map<std::size_t, std::size_t> last_pos;
    std::vector<std::size_t> res;
    std::size_t n, q, current = 1;

    std::cin >> n >> q;

    FenwickTree tree(n);

    arr.resize(n + 1);
    queries.resize(q);
    res.resize(q);

    for (std::size_t i = 1; i <= n; ++i) {
        std::cin >> arr[i];
    }

    for (std::size_t i = 0; i < q; ++i) {
        std::cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    std::sort(queries.begin(), queries.end());

    for (auto const& query : queries) {
        while (current <= query.r) {
            if (last_pos.contains(arr[current])) {
                tree.update(last_pos[arr[current]], -1);
            }

            tree.update(current, 1);
            last_pos[arr[current]] = current;
            ++current;
        }

        res[query.id] = tree.query(query.l, query.r);
    }

    for (auto const& x : res) {
        std::cout << x << "\n";
    }

    return 0;
}