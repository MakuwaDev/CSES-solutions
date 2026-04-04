#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr std::size_t MAXN = 1e5 + 5;

std::array<std::size_t, MAXN> rep;
std::array<std::size_t, MAXN> size;

std::size_t find_set(std::size_t v) {
    if (v == rep[v]) {
        return v;
    }

    return rep[v] = find_set(rep[v]);
}

void union_set(std::size_t a, std::size_t b) {
    std::size_t x = rep[a];
    std::size_t y = rep[b];

    if (x != y) {
        if (size[x] < size[y]) {
            std::swap(x, y);
        }

        rep[y] = x;
        size[x] += size[y];
    }
}

struct edge {
    std::size_t a;
    std::size_t b;
    std::size_t c;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fill(size.begin(), size.end(), 1);
    std::iota(rep.begin(), rep.end(), 0);

    std::vector<edge> edges;
    std::size_t n, m, a, b, c, res = 0, added = 0;

    std::cin >> n >> m;

    edges.resize(m);
    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        --a; --b;
        edges[i] = {a, b, c};
    }

    std::sort(edges.begin(), edges.end(), [](edge const& a, edge const& b) {
        return a.c < b.c;
    });

    for (auto const& e : edges) {
        a = find_set(e.a);
        b = find_set(e.b);

        if (a != b) {
            ++added;
            union_set(a, b);
            res += e.c;
        }
    }

    if (added != n - 1) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        std::cout << res << "\n";
    }

    return 0;
}