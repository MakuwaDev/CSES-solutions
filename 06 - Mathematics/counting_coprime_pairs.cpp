#include <iostream>
#include <vector>
#include <numeric>
#include <bit>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, res;
    std::vector<std::size_t> sieve;
    std::vector<std::size_t> primes;
    std::vector<std::size_t> cnt;
    std::vector<std::size_t> num_prime;

    sieve.resize(1e6 + 6);
    cnt.resize(1e6 + 6, 0);
    num_prime.resize(1e6 + 6, 0);
    std::iota(sieve.begin(), sieve.end(), 0);

    for (std::size_t i = 2; i * i < sieve.size(); ++i) {
        if (sieve[i] == i) {
            sieve[i] = i;
            primes.push_back(i);

            for (std::size_t j = i * i; j < sieve.size(); j += i) {
                sieve[j] = i;
            }
        }
    }

    std::cin >> n;
    res = n * (n - 1) / 2;

    for (std::size_t _ = 0; _ < n; ++_) {
        std::size_t x, p, product;
        std::vector<std::size_t> factors;

        std::cin >> x;

        while (x > 1) {
            p = sieve[x];
            factors.push_back(p);

            while (x % p == 0) {
                x /= p;
            }
        }

        for (std::size_t mask = 1; mask < (static_cast<std::size_t>(1) << factors.size()); ++mask) {
            product = 1;

            for (std::size_t i = 0; i < factors.size(); ++i) {
                if (mask & (1 << i)) {
                    product *= factors[i];
                }
            }

            ++cnt[product];
            num_prime[product] = std::popcount(mask);
        }
    }

    for (std::size_t i = 0; i < 1e6 + 6; ++i) {
        if (cnt[i]) {
            res += num_prime[i] & 1 ? -(cnt[i] * (cnt[i] - 1) / 2) : (cnt[i] * (cnt[i] - 1) / 2);
        }
    }

    std::cout << res << "\n";
    return 0;
}