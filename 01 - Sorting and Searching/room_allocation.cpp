#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct event {
    std::size_t time;
    std::size_t customer;
    bool type;  // 0 - arrival, 1 - departure
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<event> events;
    std::vector<std::size_t> allocations;
    std::set<std::size_t> rooms;
    std::size_t n, a, b, cnt = 0;

    std::cin >> n;
    events.resize(2 * n);
    allocations.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a >> b;
        events[i] = {a, i, 0};
        events[i + n] = {b, i, 1};
    }

    std::sort(events.begin(), events.end(), [](auto const& a, auto const& b) {
        return a.time != b.time ? a.time < b.time : a.type < b.type;
    });

    for (auto const& e : events) {
        if (e.type) {
            rooms.insert(allocations[e.customer]);
            continue;
        }

        if (rooms.empty()) {
            rooms.insert(++cnt);
        }

        auto it = rooms.begin();
        allocations[e.customer] = *it;
        rooms.erase(it);
    }

    std::cout << cnt << "\n";
    for (auto const& r : allocations) {
        std::cout << r << " ";
    }

    std::cout << "\n";
    return 0;
}