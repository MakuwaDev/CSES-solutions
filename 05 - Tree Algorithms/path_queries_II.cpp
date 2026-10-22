#include <iostream>
#include <vector>

class HLD {
public:
    HLD(std::size_t n, std::vector<std::vector<std::size_t>> const& adj, std::vector<std::size_t> const& val)
        : n(n), adj(adj), parent(n), depth(n), heavy(n, -1), head(n), pos(n), tree(n), curr_pos(0) {
        dfs(0, 0, 0);
        decompose(0, 0);

        tree.build([&]() {
            std::vector<std::size_t> hld_vals(n);

            for (std::size_t i = 0; i < n; ++i) {
                hld_vals[pos[i]] = val[i];
            }

            return hld_vals;
        }());
    };

    void update(std::size_t v, std::size_t val) {
        tree.update(pos[v], val);
    }

    std::size_t query(std::size_t a, std::size_t b) const {
        std::size_t res = 0;

        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]]) {
                std::swap(a, b);
            }

            res = std::max(res, tree.query(pos[head[b]], pos[b]));
            b = parent[head[b]];
        }

        if (depth[a] > depth[b]) {
            std::swap(a, b);
        }

        res = std::max(res, tree.query(pos[a], pos[b]));
        return res;
    }

private:
    struct SegmentTree {
        std::size_t n;
        std::vector<std::size_t> tree;

        SegmentTree(std::size_t n) : n(n), tree(2 * n, 0) {}

        void build (std::vector<std::size_t> const& arr) {
            for (std::size_t i = 0; i < n; ++i) {
                tree[n + i] = arr[i];
            }
            for (std::size_t i = n - 1; i > 0; --i) {
                tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
            }
        }

        void update(std::size_t p, std::size_t val) {
            for (tree[p += n] = val; p > 1; p >>= 1) {
                tree[p >> 1] = std::max(tree[p], tree[p ^ 1]);
            }
        }

        std::size_t query(std::size_t l, std::size_t r) const {
            std::size_t res = 0;
            for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = std::max(res, tree[l++]);
                if (r & 1) res = std::max(res, tree[--r]);
            }
            return res;
        }
    };

    std::size_t n;
    std::vector<std::vector<std::size_t>> adj;
    std::vector<std::size_t> parent, depth, heavy, head, pos;
    SegmentTree tree;
    std::size_t curr_pos;

    std::size_t dfs(std::size_t v, std::size_t p, std::size_t d) {
        std::size_t size = 1, max_size = 0, u_size;

        parent[v] = p;
        depth[v] = d;

        for (auto const& u : adj[v]) {
            if (u != p) {
                u_size = dfs(u, v, d + 1);
                size += u_size;

                if (u_size > max_size) {
                    max_size = u_size;
                    heavy[v] = u;
                }
            }
        }

        return size;
    }

    void decompose(std::size_t v, std::size_t h) {
        head[v] = h;
        pos[v] = curr_pos++;

        if (heavy[v] != static_cast<std::size_t>(-1)) {
            decompose(heavy[v], h);
        }

        for (auto const& u : adj[v]) {
            if (u != parent[v] && u != heavy[v]) {
                decompose(u, u);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, q, a, b;
    char c;
    std::vector<std::size_t> val;
    std::vector<std::vector<std::size_t>> graph;

    std::cin >> n >> q;

    val.resize(n);
    graph.resize(n);

    for (auto& x : val) {
        std::cin >> x;
    }

    for (std::size_t i = 1; i < n; ++i) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    HLD hld(n, graph, val);

    while (q--) {
        std::cin >> c >> a >> b;

        if (c == '1') {
            hld.update(a - 1, b);
        } else {
            std::cout << hld.query(a - 1, b - 1) << " ";
        }
    }

    std::cout << "\n";
    return 0;
}