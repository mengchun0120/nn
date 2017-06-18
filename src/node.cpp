#include "edge.hpp"
#include "weight.hpp"
#include "node.hpp"
#include "act_func.hpp"

Node::Node(ActFunc *act_func):
    act_(0),
    output_(0),
    act_der_(0),
    error_(0),
    act_func_(act_func)
{

}

void Node::add_in_edge(Edge *e)
{
    in_edges_.push_back(e);
}

Edge *Node::find_in_edge(Node *tail, Node *head)
{
    for(auto it = in_edges_.begin(); it != in_edges_.end(); ++it) {
        Edge *e = *it;
        if(e->tail() == tail && e->head() == head) {
            return e;
        }
    }
    return nullptr;
}

void Node::add_out_edge(Edge *e)
{
    out_edges_.push_back(e);
}

Edge *Node::find_out_edge(Node *tail, Node *head)
{
    for(auto it = out_edges_.begin(); it != in_edges_.end(); ++it) {
        Edge *e = *it;
        if(e->tail() == tail && e->head() == head) {
            return e;
        }
    }
    return nullptr;
}

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
