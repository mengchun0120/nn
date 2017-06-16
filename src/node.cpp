#include <cassert>
#include <algorithm>
#include "node.hpp"

void Node::add_in_weight(Index weight_id)
{
    assert(std::find(in_weights_.begin(), in_weights_.end(), weight_id) == in_weights_.end());
    in_weights_.push_back(weight_id);
}

void Node::add_out_weight(Index weight_id)
{
    assert(std::find(out_weights_.begin(), out_weights_.end(), weight_id) == out_weights_.end());
    out_weights_.push_back(weight_id);
}
