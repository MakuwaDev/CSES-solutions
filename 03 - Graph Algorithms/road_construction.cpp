#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <concepts>
#include <functional>

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

template <typename T>
    requires Hashable<T> && std::equality_comparable<T>
class DSU {
public:
    DSU() = default;

    DSU(std::vector<T> const& elements) {
        std::size_t n = elements.size();
        parent.resize(n);
        size.resize(n, 1);

        std::iota(parent.begin(), parent.end(), 0);

        for (std::size_t i = 0; i < n; ++i) {
            id[elements[i]] = i;
        }

        count_ = n;
        max_size_ = (n > 0) ? 1 : 0;
    }

    bool make_set(T const& x) {
        if (id.contains(x)) {
            return false;
        }

        std::size_t new_idx = id.size();
        id[x] = new_idx;

        parent.push_back(new_idx);
        size.push_back(1);

        ++count_;

        max_size_ = max_size_ ? max_size_ : 1;

        return true;
    }

    bool union_set(T const& a, T const& b) {
        if (!id.contains(a) || !id.contains(b)) {
            return false;
        }

        std::size_t x = find_set(id[a]);
        std::size_t y = find_set(id[b]);

        if (x != y) {
            if (size[x] < size[y]) {
                std::swap(x, y);
            }

            parent[y] = x;
            size[x] += size[y];

            --count_;
            max_size_ = std::max(size[x], max_size_);
        }

        return true;
    }

    bool same_set(T const& a, T const& b) {
        if (!id.contains(a) || !id.contains(b)) {
            return false;
        }

        return find_set(id[a]) == find_set(id[b]);
    }

    std::size_t count() {
        return count_;
    }

    std::size_t max_size() {
        return max_size_;
    }

private:
    std::unordered_map<T, std::size_t> id;
    std::vector<std::size_t> parent;
    std::vector<std::size_t> size;

    std::size_t count_;
    std::size_t max_size_;

    std::size_t find_set(std::size_t v) {
        if (v == parent[v]) {
            return v;
        }

        return parent[v] = find_set(parent[v]);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::size_t> cities;
    std::size_t n, m, a, b;
    std::cin >> n >> m;

    cities.resize(n);
    std::iota(cities.begin(), cities.end(), 1);

    DSU<std::size_t> dsu(cities);

    while (m--) {
        std::cin >> a >> b;
        dsu.union_set(a, b);
        std::cout << dsu.count() << " " << dsu.max_size() << "\n";
    }

    return 0;
}