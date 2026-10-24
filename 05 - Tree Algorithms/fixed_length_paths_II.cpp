#include <iostream>
#include <vector>
 
class CD {
public:
    CD(std::vector<std::vector<std::size_t>> adj)
     : adj(adj) {
        removed.resize(adj.size(), false);
        subtree_size.resize(adj.size(), 0);
        res = 0;
    }
 
    std::size_t calculate_path_count(std::size_t k1, std::size_t k2) {
        this->k1 = k1;
        this->k2 = k2;
 
        decompose(0);
        return res;
    }
private:
    struct Fenwick {
        std::size_t n;
        std::vector<std::size_t> tree;
 
        Fenwick(std::size_t n)
         : n(n) {
            tree.resize(n + 1, 0);
        }
 
        void add(std::size_t i, std::size_t x) {
            for (++i; i <= n; i += i & -i) {
                tree[i] += x;
            }
        }
 
        std::size_t query(std::size_t i) {
            std::size_t sum = 0;
            i = std::min(i, n - 1);
 
            for (++i; i > 0; i -= i & -i) {
                sum += tree[i];
            }
 
            return sum;
        }
    };
 
    std::vector<std::vector<std::size_t>> adj;
    std::vector<bool> removed;
    std::vector<std::size_t> subtree_size;
 
    std::size_t k1, k2;
    std::size_t res;
 
    std::size_t calculate_subtree_sizes(std::size_t v, std::size_t p = static_cast<std::size_t>(-1)) {
        subtree_size[v] = 1;
 
        for (auto const& u : adj[v]) {
            if (u != p && !removed[u]) {
                subtree_size[v] += calculate_subtree_sizes(u, v);
            }
        }
 
        return subtree_size[v];
    }
 
    std::size_t get_centroid(std::size_t v, std::size_t size, std::size_t p = static_cast<std::size_t>(-1)) {
        for (auto const& u : adj[v]) {
            if (u == p || removed[u]) {
                continue;
            }
 
            if (2 * subtree_size[u] > size) {
                return get_centroid(u, size, v);
            }
        }
 
        return v;
    }
 
    void get_distances(std::size_t v, std::size_t p, std::size_t dist, std::vector<std::size_t>& distances) {
        if (dist > k2) {
            return;
        }
 
        distances.push_back(dist);
 
        for (auto const& u : adj[v]) {
            if (u != p && !removed[u]) {
                get_distances(u, v, dist + 1, distances);
            }
        }
    }
 
    void process_centroid(std::size_t v, std::size_t size) {
        Fenwick bit(size + 1);
        std::vector<std::size_t> current_distances;
 
        bit.add(0, 1);
 
        for (auto const& u : adj[v]) {
            if (removed[u]) {
                continue;
            }
 
            current_distances.clear();
            get_distances(u, v, 1, current_distances);
 
            for (auto const& d : current_distances) {
                if (k2 >= d) {
                    res += bit.query(k2 - d);
                }
 
                if (k1 > d) {
                    res -= bit.query(k1 - d - 1);
                }
            }
 
            for (auto const& d : current_distances) {
                bit.add(d, 1);
            }
        }
    }
 
    void decompose(std::size_t v) {
        std::size_t size = calculate_subtree_sizes(v);
        std::size_t centroid = get_centroid(v, size);
 
        process_centroid(centroid, size);
        removed[centroid] = true;
 
        for (auto const& u : adj[centroid]) {
            if (!removed[u]) {
                decompose(u);
            }
        }
    }
};
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    std::size_t n, k1, k2, a, b;
    std::vector<std::vector<std::size_t>> graph;
 
    std::cin >> n >> k1 >> k2;
 
    graph.resize(n);
 
    for (std::size_t _ = 1; _ < n; ++_) {
        std::cin >> a >> b;
        --a; --b;
 
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
 
    CD cd(graph);
 
    std::cout << cd.calculate_path_count(k1, k2) << "\n";
    return 0;
}