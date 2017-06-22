#include <cassert>
#include "neural_net.hpp"
#include "output_model.hpp"

void IdentityOutputProc::operator()(NodeIterPair output_iter_pair)
{
    for(auto it = output_iter_pair.first; it != output_iter_pair.second; ++it) {
        it->set_output(it->act());
    }
}

double SquareLossFunc::operator()(NodeIterPair output_iter_pair, const Point& target)
{
    assert(output_iter_pair.second - output_iter_pair.first == static_cast<int>(target.size()));

    double loss = 0.0;
    size_t i = 0;

    for(auto it = output_iter_pair.first; it != output_iter_pair.second; ++it, ++i) {
        double dist = it->output() - target[i];
        loss += dist * dist;
    }
    loss /= 2.0;

    return loss;
}

void SquareLossErrorProc::operator()(NodeIterPair output_iter_pair, const Point& target)
{
    assert(output_iter_pair.second - output_iter_pair.first == static_cast<int>(target.size()));

    size_t i = 0;

    for(auto it = output_iter_pair.first; it != output_iter_pair.second; ++it, ++i) {
        it->set_error(it->act() - target[i]);
    }
}
