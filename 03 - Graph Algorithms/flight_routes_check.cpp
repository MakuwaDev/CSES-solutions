#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<std::size_t>> const& graph,
         std::vector<bool>& vis, std::vector<std::size_t>& out, std::size_t v) {
    vis[v] = true;

    for (auto u : graph[v]) {
        if (!vis[u]) {
            dfs(graph, vis, out, u);
        }
    }

    out.push_back(v);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<bool> vis;
    std::vector<std::size_t> postorder, tmp;
    std::vector<std::vector<std::size_t>> g, t;
    std::size_t n, m, a, b, prev;
    bool second = false;

    std::cin >> n >> m;

    g.resize(n + 1);
    t.resize(n + 1);
    vis.resize(n + 1);

    while (m--) {
        std::cin >> a >> b;
        g[a].push_back(b);
        t[b].push_back(a);
    }

    for (std::size_t i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(g, vis, postorder, i);
        }
    }

    std::fill(vis.begin(), vis.end(), false);

    while (!postorder.empty()) {
        a = postorder.back();
        postorder.pop_back();

        if (!vis[a]) {
            if (second) {
                std::cout << "NO\n" << a << " " << prev << "\n";
                return 0;
            } else {
                dfs(t, vis, tmp, a);
                second = true;
                prev = a;
            }
        }
    }

    std::cout << "YES\n";
    return 0;
}