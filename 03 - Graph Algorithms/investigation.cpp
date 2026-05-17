#include <iostream>
#include <vector>
#include <queue>

constexpr std::size_t MOD = 1e9 + 7;
constexpr std::size_t INF = 1e16 + 16;

struct entry {
    std::size_t v;
    std::size_t d;

    bool operator> (entry const& other) const {
        return d > other.d;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<std::pair<std::size_t, std::size_t>>> graph;
    std::vector<std::size_t> dist;
    std::vector<std::size_t> cnt;
    std::vector<std::size_t> mindist;
    std::vector<std::size_t> maxdist;
    std::priority_queue<entry, std::vector<entry>, std::greater<entry>> q;
    std::size_t n, m, a, b, c;

    std::cin >> n >> m;

    graph.resize(n + 1);
    dist.resize(n + 1, INF);
    cnt.resize(n + 1);
    mindist.resize(n + 1);
    maxdist.resize(n + 1);

    while (m--) {
        std::cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    dist[1] = 0;
    cnt[1] = 1;
    mindist[1] = 0;
    maxdist[1] = 0;

    q.push({1, 0});

    while (!q.empty()) {
        auto [v, d] = q.top();
        q.pop();

        if (d > dist[v]) {
            continue;
        }

        for (auto const& [u, w] : graph[v]) {
            if (d + w < dist[u]) {
                dist[u] = d + w;
                cnt[u] = cnt[v];
                mindist[u] = mindist[v] + 1;
                maxdist[u] = maxdist[v] + 1;
                q.push({u, dist[u]});
            } else if (d + w == dist[u]) {
                cnt[u] = (cnt[u] + cnt[v]) % MOD;
                mindist[u] = std::min(mindist[u], mindist[v] + 1);
                maxdist[u] = std::max(maxdist[u], maxdist[v] + 1);
            }
        }
    }

    std::cout << dist[n] << " " << cnt[n] << " " << mindist[n] << " " << maxdist[n] << "\n";
    return 0;
}