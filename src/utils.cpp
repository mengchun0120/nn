#include <cassert>
#include <cmath>
#include <cstddef>
#include "utils.hpp"

double euclid_dist(const Point& p1, const Point& p2)
{
    assert(p1.size() == p2.size());

    double total = 0.0;

    for(size_t i = 0; i < p1.size(); ++i) {
        double d = p1[i] - p2[i];
        total += d * d;
    }

    return sqrt(total);
}
