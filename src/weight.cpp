#include "node.hpp"
#include "edge.hpp"
#include "weight.hpp"

double Weight::cal_der()
{
    double d = 0.0;
    for(auto it = edges_.begin(); it != edges_.end(); ++it) {
        Edge *e = *it;
        d += e->tail()->output() * e->head()->error();
    }
    return d;
}
