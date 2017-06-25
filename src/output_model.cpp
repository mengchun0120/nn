#include <cassert>
#include "neural_net.hpp"
#include "output_model.hpp"

void IdentityOutputProc::operator()(Group<Node>::Range outputs)
{
    for(auto it = outputs.first; it != outputs.second; ++it) {
        it->set_output(it->act());
    }
}

double SquareLossFunc::operator()(Group<Node>::Range outputs, const Point& target)
{
    assert(Group<Node>::size(outputs) == target.size());

    double loss = 0.0;
    size_t i = 0;

    for(auto it = outputs.first; it != outputs.second; ++it, ++i) {
        double dist = it->output() - target[i];
        loss += dist * dist;
    }
    loss /= 2.0;

    return loss;
}

void SquareLossErrorProc::operator()(Group<Node>::Range outputs, const Point& target)
{
    assert(Group<Node>::size(outputs) == target.size());

    size_t i = 0;

    for(auto it = outputs.first; it != outputs.second; ++it, ++i) {
        it->set_error(it->act() - target[i]);
    }
}
