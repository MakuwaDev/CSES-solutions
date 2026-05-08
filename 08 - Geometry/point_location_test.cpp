#include <iostream>
#include <cstdint>

struct point {
    int64_t x;
    int64_t y;
};

int64_t cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t q;
    int64_t cp;
    point p1, p2, p3;
    std::cin >> q;
    
    while (q--) {
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        cp = cross(p1, p2, p3);

        if (cp > 0) {
            std::cout << "LEFT\n";
        } else if (cp < 0) {
            std::cout << "RIGHT\n";
        } else {
            std::cout << "TOUCH\n";
        }
    }

    return 0;
}