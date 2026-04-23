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

void dfs2(std::vector<std::vector<std::size_t>> const& graph,
         std::vector<std::size_t>& kingdom, std::size_t k, std::size_t v) {

    kingdom[v] = k;

    for (auto u : graph[v]) {
        if (!kingdom[u]) {
            dfs2(graph, kingdom, k, u);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<bool> vis;
    std::vector<std::size_t> postorder;
    std::vector<std::size_t> kingdom;
    std::vector<std::vector<std::size_t>> g, t;
    std::size_t n, m, a, b, res = 0;

    std::cin >> n >> m;

    g.resize(n + 1);
    t.resize(n + 1);
    vis.resize(n + 1);
    kingdom.resize(n + 1);

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

        if (!kingdom[a]) {
            dfs2(t, kingdom, ++res, a);
        }
    }

    std::cout << res << "\n";
    for (std::size_t i = 1; i <= n; ++i) {
        std::cout << kingdom[i] << " ";
    }

    std::cout << "\n";
    return 0;
}