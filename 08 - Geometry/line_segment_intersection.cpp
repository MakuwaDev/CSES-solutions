#include <iostream>
#include <cstdint>

class Point {
public:
    int64_t x, y;

    Point() {}
    Point(int64_t x, int64_t y) : x(x), y(y) {}

    Point operator-(Point const& p) const {
        return Point(x - p.x, y - p.y);
    }

    int64_t cross(Point const& p) const {
        return x * p.y - y * p.x;
    }

    int64_t cross(Point const& a, Point const& b) const {
        return (a - *this).cross(b - *this);
    }
};

class Segment {
public:
    Point a, b;

    Segment() {}
    Segment(Point const& a, Point const& b) : a(a), b(b) {}

    bool intersect(Segment const& s) {
        auto const& c = s.a;
        auto const& d = s.b;

        if (!c.cross(a, d) && !c.cross(b, d)) {
            return bounding(a.x, b.x, c.x, d.x) && bounding(a.y, b.y, c.y, d.y);
        }

        return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) && sgn(c.cross(d, a)) != sgn(c.cross(d, b));
    }

private:
    int64_t sgn(int64_t val) {
        return (0 < val) - (val < 0);
    }

    bool bounding(int64_t a, int64_t b, int64_t c, int64_t d) {
        if (a > b) {
            std::swap(a, b);
        }

        if (c > d) {
            std::swap(c, d);
        }

        return std::max(a, c) <= std::min(b, d);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t t;
    Segment s1, s2;

    std::cin >> t;

    while (t--) {
        std::cin >> s1.a.x >> s1.a.y >> s1.b.x >> s1.b.y >> s2.a.x >> s2.a.y >> s2.b.x >> s2.b.y;
        std::cout << (s1.intersect(s2) ? "YES" : "NO") << "\n";
    }

    return 0;
}