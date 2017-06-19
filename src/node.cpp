#include "edge.hpp"
#include "weight.hpp"
#include "node.hpp"
#include "act_func.hpp"

void Node::feed_forward()
{
    act_ = 0.0;
    for(auto it = in_edges_.begin(); it != in_edges_.end(); ++it) {
        Edge *e = *it;
        act_ += e->tail()->output() * e->weight()->value();
    }
    if(act_func_) {
        output_ = act_func_->act(this);
    }
}

void Node::back_prop()
{
    error_ = 0.0;
    for(auto it = out_edges_.begin(); it != out_edges_.end(); ++it) {
        Edge *e = *it;
        error_ += e->head()->error() * e->weight()->value();
    }
    if(act_func_) {
        error_ *= act_func_->act_der(this);
    }
}
