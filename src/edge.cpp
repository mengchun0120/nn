#include <cassert>
#include "node.hpp"
#include "weight.hpp"
#include "edge.hpp"

void Edge::cal_add_der()
{
    assert(tail_ && head_);
    double der = tail_->output() * head_->error();
    weight_->add_der(der);
}
