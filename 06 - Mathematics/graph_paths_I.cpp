#include <iostream>
#include <vector>

constexpr std::size_t MOD = 1e9 + 7;

struct Matrix {
private:
    std::vector<std::vector<std::size_t>> m;

public:
    Matrix(std::size_t a, std::size_t b) {
        m.resize(a);
        for (auto& v : m) {
            v.resize(b);
        }
    }

    std::pair<std::size_t, std::size_t> size() const {
        return {m.size(), m[0].size()};
    }

    void set(std::size_t i, std::size_t j, std::size_t x) {
        m[i][j] = x;
    }

    std::size_t get(std::size_t i, std::size_t j) const {
        return m[i][j];
    }

    Matrix operator*(Matrix const& m2) const {
        Matrix r(m.size(), m2.size().second);

        for (std::size_t i = 0; i < m.size(); ++i) {
            for (std::size_t j = 0; j < m2.size().second; ++j) {
                std::size_t x = 0;

                for (std::size_t k = 0; k < m2.size().first; ++k) {
                    x = (x + (m[i][k] * m2.m[k][j]) % MOD) % MOD;
                }

                r.set(i, j, x);
            }
        }

        return r;
    }

    Matrix operator^(std::size_t b) const {
        Matrix res(m.size(), m.size());
        Matrix pow = *this;

        for (std::size_t i = 0; i < m.size(); ++i) {
            res.set(i, i, 1);
        }

        while (b > 0) {
            if (b & 1) {
                res = res * pow;
            }

            pow = pow * pow;
            b >>= 1;
        }

        return res;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m, a, b, k;

    std::cin >> n >> m >> k;

    Matrix graph(n, n);

    while (m--) {
        std::cin >> a >> b;
        graph.set(a - 1, b - 1, graph.get(a - 1, b - 1) + 1);
    }

    graph = graph ^ k;

    std::cout << graph.get(0, n - 1) << "\n";
    return 0;
}