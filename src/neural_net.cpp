#include "output_model.hpp"
#include "neural_net.hpp"
#include <iostream>

using namespace std;

NeuralNet::NeuralNet(size_t num_nodes, size_t num_edges, size_t num_weights, OutputModel *output_model):
    nodes_(num_nodes),
    weights_(num_weights),
    edges_(num_edges),
    input_start_(0),
    input_size_(0),
    output_start_(0),
    output_size_(0)
{
    assert(output_model);
    output_model_ = output_model;
}

void NeuralNet::set_input(size_t input_start, size_t input_size)
{
    assert(input_start < nodes_.size() && input_start + input_size <= nodes_.size());
    input_start_ = input_start;
    input_size_ = input_size;
}

void NeuralNet::set_output(size_t output_start, size_t output_size)
{
    assert(output_start < nodes_.size() && output_start + output_size <= nodes_.size());
    output_start_ = output_start;
    output_size_ = output_size;
}

void NeuralNet::bind_edge(size_t edge_idx, size_t tail_idx, size_t head_idx, size_t weight_idx)
{
    Edge *e = edge(edge_idx);
    Node *tail = node(tail_idx);
    e->set_tail(tail);
    tail->add_out_edge(e);

    Node *head = node(head_idx);
    e->set_head(head);
    head->add_in_edge(e);

    Weight *w = weight(weight_idx);
    e->set_weight(w);
    w->add_edge(e);
}

void NeuralNet::init_input(const std::vector<double>& input)
{
    assert(input.size() == input_size_);
    for(size_t i = input_start_, j = 0; j < input_size_; ++i, ++j) {
        nodes_[i].set_output(input[j]);
    }
}

void NeuralNet::clear_node_flags()
{
    for(auto it = nodes_.begin(); it != nodes_.end(); ++it) {
        it->clear_flag();
    }
}

void NeuralNet::add_out_nodes_to_queue(Node *n)
{
    for(size_t k = 0; k < n->num_out_edges(); ++k) {
        Node *n1 = n->out_edge(k)->head();
        if(n1->flag() != STAGE_FEED_FORWARD) {
            queue_.push_back(n1);
            n1->set_flag(STAGE_FEED_FORWARD);
        }
    }
}

void NeuralNet::init_queue_feed_forward()
{
    queue_.clear();
    for(size_t i = input_start_, j = 0; j < input_size_; ++i, ++j) {
        add_out_nodes_to_queue(node(i));
    }
}

void NeuralNet::init_feed_forward(const std::vector<double>& input)
{
    init_input(input);
    clear_node_flags();
    init_queue_feed_forward();
}

double NeuralNet::feed_forward(const std::vector<double>& input, const std::vector<double>& target)
{
    init_feed_forward(input);
    while(!queue_.empty()) {
        Node *n = queue_.front();
        queue_.pop_front();

        n->feed_forward();

        add_out_nodes_to_queue(n);
    }

    output_model_->get_output(this);

    double loss = output_model_->get_loss(this, target);

    return loss;
}

void NeuralNet::add_in_nodes_to_queue(Node *n)
{
    for(size_t k = 0; k < n->num_in_edges(); ++k) {
        Node *n1 = n->in_edge(k)->tail();
        if(n1->num_in_edges() > 0 && n1->flag() != STAGE_BACK_PROP) {
            queue_.push_back(n1);
            n1->set_flag(STAGE_BACK_PROP);
        }
    }
}

void NeuralNet::init_queue_back_prop()
{
    for(size_t i = output_start_, j = 0; j < output_size_; ++i, ++j) {
        add_in_nodes_to_queue(node(i));
    }
}

void NeuralNet::init_back_prop(const std::vector<double>& target)
{
    output_model_->get_output_error(this, target);
    init_queue_back_prop();
}

void NeuralNet::back_prop(const std::vector<double>& target)
{
    init_back_prop(target);
    while(!queue_.empty()) {
        Node *n = queue_.front();
        queue_.pop_front();

        n->back_prop();

        add_in_nodes_to_queue(n);
    }
}

void NeuralNet::add_gradient()
{
    for(auto it = weights_.begin(); it != weights_.end(); ++it) {
        double der = it->cal_der();
        it->set_der(it->der() + der);
    }
}
