#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<std::size_t>> graph, trans, sccgraph;
std::vector<std::size_t> scc;
std::vector<bool> vis;
std::vector<std::size_t> post;
std::vector<std::size_t> order;
std::vector<std::size_t> in;
std::vector<std::size_t> points;
std::vector<std::size_t> sccpoints;
std::vector<std::size_t> dp;

void dfs1(std::size_t v) {
    vis[v] = true;

    for (auto const& u : graph[v]) {
        if (!vis[u]) {
            dfs1(u);
        }
    }

    post.push_back(v);
}

void dfs2(std::size_t v, std::size_t s) {
    scc[v] = s;

    for (auto const& u : trans[v]) {
        if (!scc[u]) {
            dfs2(u, s);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::queue<std::size_t> q;
    std::size_t n, m, a, b, s = 0, res = 0;

    std::cin >> n >> m;

    graph.resize(n);
    trans.resize(n);
    points.resize(n);
    vis.resize(n);
    post.resize(n);
    scc.resize(n);

    for (auto& x : points) {
        std::cin >> x;
    }


    while (m--) {
        std::cin >> a >> b;
        --a; --b;

        graph[a].push_back(b);
        trans[b].push_back(a);
    }

    for (std::size_t v = 0; v < n; ++v) {
        if (!vis[v]) {
            dfs1(v);
        }
    }

    while (!post.empty()) {
        a = post.back();
        post.pop_back();

        if (!scc[a]) {
            dfs2(a, ++s);
        }
    }

    for (auto& x : scc) {
        --x;
    }

    sccgraph.resize(s);
    in.resize(s);
    sccpoints.resize(s);
    dp.resize(s);

    for (std::size_t v = 0; v < n; ++v) {
        sccpoints[scc[v]] += points[v];

        for (auto const& u : graph[v]) {
            if (scc[v] != scc[u]) {
                ++in[scc[u]];
                sccgraph[scc[v]].push_back(scc[u]);
            }
        }
    }

    for (std::size_t v = 0; v < s; ++v) {
        if (!in[v]) {
            q.push(v);
        }
    }

    while (!q.empty()) {
        a = q.front();
        q.pop();
        order.push_back(a);

        for (auto const& b : sccgraph[a]) {
            if (!(--in[b])) {
                q.push(b);
            }
        }
    }

    while (!order.empty()) {
        a = order.back();
        order.pop_back();

        for (auto const& b : sccgraph[a]) {
            dp[a] = std::max(dp[a], dp[b]);
        }

        dp[a] += sccpoints[a];
    }

    for (auto const& x : dp) {
        res = std::max(res, x);
    }

    std::cout << res << "\n";
    return 0;
}