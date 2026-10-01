#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

constexpr int64_t INF = std::numeric_limits<int64_t>::max();

class Point {
public:
    int64_t x;
    int64_t y;

    bool operator==(Point const& p) const {
        if (x == p.x && y == p.y) {
            return true;
        }

        return false;
    }

    int64_t product(Point b, Point c) const {
        return ((c.x - x) * (b.y - y) - (b.x - x) * (c.y - y));
    }

    bool cmp(Point b, Point origin) const {
        if (*this == origin) {
            return true;
        }

        if (b == origin) {
            return false;
        }

        if (origin.product(*this, b) == 0) {
            return x == b.x ? y < b.y : x < b.x;
        }

        return origin.product(*this, b) < 0;
    }
};

std::vector<Point> get_convex(std::vector<Point> const& points) {
    Point origin = {INF, INF};
    std::size_t rev;
    std::vector<Point> convex, _points = points;

    for (auto const& p : points) {
        if (p.x < origin.x || (p.x == origin.x && p.y < origin.y)) {
            origin = p;
        }
    }

    std::sort(_points.begin(), _points.end(), [&origin](Point const& a, Point const& b) {
        return a.cmp(b, origin);
    });

    rev = _points.size() - 1;

    while (rev > 0 && origin.product(_points.back(), _points[rev - 1]) == 0) {
        --rev;
    }

    std::reverse(_points.begin() + rev, _points.end());

    for (std::size_t i = 0; i < _points.size(); ++i) {
        while (convex.size() >= 2 && convex[convex.size() - 2].product(convex.back(), _points[i]) > 0) {
            convex.pop_back();
        }

        convex.push_back(_points[i]);
    }

    return convex;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::vector<Point> points;

    std::cin >> n;
    points.resize(n);

    for (auto& p : points) {
        std::cin >> p.x >> p.y;
    }

    auto convex = get_convex(points);
    std::cout << convex.size() << "\n";

    for (auto const& p : convex) {
        std::cout << p.x << " " << p.y << "\n";
    }

    return 0;
}