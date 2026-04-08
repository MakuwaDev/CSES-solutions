#include <iostream>
#include <vector>

constexpr std::size_t MAXN = 2e5 + 5;
constexpr std::size_t MAXPOW = 20;

std::vector<std::size_t> graph[MAXN];
std::size_t depth[MAXN];
std::size_t ancestors[MAXN][MAXPOW + 1];

void init(std::size_t v = 1, std::size_t father = 1) {
	depth[v] = depth[father] + 1;
	ancestors[v][0] = father;

	for (std::size_t i = 1; i <= MAXPOW; ++i) {
		ancestors[v][i] = ancestors[ancestors[v][i - 1]][i - 1];
    }

	for (auto x : graph[v]) {
		if (x != father) init(x, v);
    }
}

std::size_t lca(std::size_t a, std::size_t b) {
	if (a == b) {
        return a;
    }

	if (depth[a] > depth[b]) {
        std::swap(a, b);
    }

	for (std::size_t i = MAXPOW; i <= MAXPOW; --i) {
		if (depth[ancestors[b][i]] >= depth[a]){
            b = ancestors[b][i];
        }
    }

	if (a == b) {
        return a;
    }

	for (std::size_t i = MAXPOW; i <= MAXPOW; --i) {
		if (ancestors[a][i] != ancestors[b][i]) {
			a = ancestors[a][i];
			b = ancestors[b][i];
		}
    }

	return ancestors[a][0];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::size_t n, q, a, b, l;

	std::cin >> n >> q;

	for (std::size_t i = 0; i < n - 1; ++i) {
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	depth[1] = -1;
	init();

    while (q--) {
        std::cin >> a >> b;
        l = lca(a, b);
        std::cout << depth[a] + depth[b] - 2 * depth[l] << "\n";
    }

    return 0;
}