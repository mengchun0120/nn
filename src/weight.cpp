#include "node.hpp"
#include "edge.hpp"
#include "weight.hpp"

void Weight::add_edge(Edge *e)
{
    edges_.push_back(e);
}

double Weight::cal_der()
{
    der_ = 0.0;
    for(auto it = edges_.begin(); it != edges_.end(); ++it) {
        Edge *e = *it;
        der_ += e->tail()->output() * e->head()->error();
    }
    return der_;
}
