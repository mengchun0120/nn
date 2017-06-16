#include <algorithm>
#include <cassert>
#include "weight.hpp"

void Weight::add_tail(Index node_id)
{
    assert(std::find(tails_.begin(), tails_.end(), node_id) == tails_.end());
    tails_.push_back(node_id);
}

void Weight::add_head(Index node_id)
{
    assert(std::find(heads_.begin(), heads_.end(), node_id) == heads_.end());
    heads_.push_back(node_id);
}
