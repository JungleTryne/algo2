//
// Created by jungletryne on 08.04.2020.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "geometry.h"

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool equals(double left, double right) {
    return fabs(right - left) < eps;
}

TEST_CASE("Test1") {
    const int ax = -2, ay = 2, bx = 1, by = 2;
    Point a(ax, ay);
    Point b(bx, by);
    REQUIRE(equals(distance(a, b), 3));
}

TEST_CASE("Test2") {
    const int ax = -2, ay = 2, bx = 1, by = 2,
            cx = 3, cy = -1, dx = -1, dy = -2,
            ex = 1, ey = -1, fx = 6, fy = 1;
    Point a(ax, ay);
    Point b(bx, by);
    Point c(cx, cy);
    Point d(dx, dy);
    Point e(ex, ey);
    Point f(fx, fy);
    Polygon abfcd(a, b, f, c, d);
    std::vector<Point> vec = {c, f, b, a, d};
    Polygon cfbad(vec);

    REQUIRE(abfcd == cfbad);

    REQUIRE(abfcd.isConvex());
}

TEST_CASE("Test3") {
    const int ax = -2, ay = 2, bx = 1, by = 2,
            cx = 3, cy = -1, dx = -1, dy = -2,
            ex = 1, ey = -1, fx = 6, fy = 1;
    Point a(ax, ay);
    Point b(bx, by);
    Point c(cx, cy);
    Point d(dx, dy);
    Point e(ex, ey);
    Point f(fx, fy);
    Triangle abd(a, b, d);
    Polygon abfced(a, b, f, c, e, d);
    Polygon bfced(b, f, c, e, d);
    REQUIRE(equals(abd.area() + bfced.area(), abfced.area()));
}

