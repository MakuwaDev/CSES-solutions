#include <iostream>
#include <vector>
#include <cstdint>

class tree {
public:
    tree(std::vector<int64_t> const& arr) {
        size = calc_size(arr.size());
        data.resize(2 * size);

        for (std::size_t i = 0; i < arr.size(); ++i) {
            data[size + i] = arr[i];
        }

        for (std::size_t i = size - 1; i > 0; --i) {
            data[i] = std::min(data[2 * i], data[2 * i + 1]);
        }
    }

    void update(std::size_t id, int64_t x) {
        update_impl(size + id, x);
    }

    int64_t query(std::size_t first, std::size_t last) {
        return query_impl(first + size, last + size);
    }

private:
    static constexpr int64_t INF = 1e18;

    std::size_t size;
    std::vector<int64_t> data;

    std::size_t calc_size(std::size_t n) {
        std::size_t res = 1;

        while (res < n) {
            res <<= 1;
        }

        return res;
    }

    void update_impl(std::size_t id, int64_t x) {
        data[id] = x;

        id /= 2;

        while (id > 0) {
            data[id] = std::min(data[2 * id], data[2 * id + 1]);
            id /= 2;
        }
    }

    int64_t query_impl(std::size_t first, std::size_t last) {
        int64_t res = INF;

        while (first <= last) {
            if (first % 2 == 1) {
                res = std::min(res, data[first++]);
            }

            if (last % 2 == 0) {
                res = std::min(res, data[last--]);
            }

            first /= 2;
            last /= 2;
        }

        return res;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int64_t> pizza, l, r;
    std::size_t n, q, k;
    int64_t x;
    char c;

    std::cin >> n >> q;
    pizza.resize(n);

    for (auto& x : pizza) {
        std::cin >> x;
    }

    for (std::size_t i = 0; i < n; ++i) {
        l.push_back(pizza[i] - i);
        r.push_back(pizza[i] + i);
    }

    tree ltree(l);
    tree rtree(r);

    while (q--) {
        std::cin >> c >> k;
        --k;

        if (c == '1') {
            std::cin >> x;
            ltree.update(k, x - k);
            rtree.update(k, x + k);
        } else {
            std::cout << std::min(ltree.query(0, k - 1) + k, rtree.query(k, n - 1) - k) << "\n";
        }
    }

    return 0;
}