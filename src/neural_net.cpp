#include "neural_net.hpp"
#include "output_model.hpp"
#include <iostream>

using namespace std;

NeuralNet::NeuralNet(OutputModel *output_model):
    input_size_(0),
    output_size_(0),
    num_biases_(0),
    num_hiddens_(0),
    output_model_(output_model)
{

}

NodeIterPair NeuralNet::add_inputs(size_t num_inputs)
{
    input_iter_pair_ = node_groups_.add(num_inputs);
    input_size_ = num_inputs;
    return input_iter_pair_;
}

NodeIterPair NeuralNet::add_outputs(size_t num_outputs)
{
    output_iter_pair_ = node_groups_.add(num_outputs);
    output_size_ = num_outputs;
    return output_iter_pair_;
}

NodeIterPair NeuralNet::add_biases(size_t num_biases)
{
    auto biases_iter_pair = node_groups_.add(num_biases);
    num_biases_ += num_biases;
    return biases_iter_pair;
}

NodeIterPair NeuralNet::add_hiddens(size_t num_hiddens, ActFunc *act_func)
{
    auto hiddens_iter_pair = node_groups_.add(num_hiddens);
    for(auto it = hiddens_iter_pair.first; it != hiddens_iter_pair.second; ++it) {
        it->set_act_func(act_func);
    }
    num_hiddens_ += num_hiddens;
    return hiddens_iter_pair;
}

WeightIterPair NeuralNet::add_weights(size_t num_weights)
{
    return weight_groups_.add(num_weights);
}

EdgeIterPair NeuralNet::add_edges(size_t num_edges)
{
    return edge_groups_.add(num_edges);
}

EdgeIterPair NeuralNet::link(Node *tail, Node *head)
{
    auto weight_it_pair = add_weights(1);
    auto edge_it_pair = add_edges(1);
    Weight *w = &(*(weight_it_pair.first));
    Edge *edge = &(*(edge_it_pair.first));

    edge->set_tail(tail);
    edge->set_head(head);
    edge->set_weight(w);

    w->add_edge(edge);

    tail->add_out_edge(edge);
    head->add_in_edge(edge);

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(Node *tail, Node *head, Weight *weight)
{
    assert(tail && head && weight);

    auto edge_it_pair = add_edges(1);
    Edge *edge = &(*(edge_it_pair.first));

    edge->set_tail(tail);
    edge->set_head(head);
    edge->set_weight(weight);

    weight->add_edge(edge);

    tail->add_out_edge(edge);
    head->add_in_edge(edge);

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(Node *tail, NodeIterPair heads)
{
    size_t num_heads = heads.second - heads.first;

    assert(tail && num_heads > 0);

    auto edge_it_pair = add_edges(num_heads);
    auto weight_it_pair = add_weights(num_heads);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weight_it_pair.first;

    for(auto node_it = heads.first; node_it != heads.second; ++node_it, ++edge_it, ++weight_it) {
        edge_it->set_tail(tail);
        edge_it->set_head(&(*node_it));
        edge_it->set_weight(&(*weight_it));

        weight_it->add_edge(&(*edge_it));

        tail->add_out_edge(&(*edge_it));
        node_it->add_in_edge(&(*edge_it));
    }

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(Node *tail, NodeIterPair heads, WeightIterPair weights)
{
    int num_heads = heads.second - heads.first;

    assert(tail && num_heads > 0 && (weights.second - weights.first) >= num_heads);

    auto edge_it_pair = add_edges(num_heads);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weights.first;

    for(auto node_it = heads.first; node_it != heads.second; ++node_it, ++edge_it, ++weight_it) {
        edge_it->set_tail(tail);
        edge_it->set_head(&(*node_it));
        edge_it->set_weight(&(*weight_it));

        weight_it->add_edge(&(*edge_it));

        tail->add_out_edge(&(*edge_it));
        node_it->add_in_edge(&(*edge_it));
    }

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(NodeIterPair tails, NodeIterPair heads)
{
    size_t num_tails = tails.second - tails.first;
    size_t num_heads = heads.second - heads.first;

    assert(num_tails > 0 && num_heads > 0);

    size_t num_edges = num_tails * num_heads;
    auto edge_it_pair = add_edges(num_edges);
    auto weight_it_pair = add_weights(num_edges);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weight_it_pair.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it) {
        for(auto head_it = heads.first; head_it != heads.second; ++head_it, ++edge_it, ++weight_it) {
            edge_it->set_tail(&(*tail_it));
            edge_it->set_head(&(*head_it));
            edge_it->set_weight(&(*weight_it));

            weight_it->add_edge(&(*edge_it));

            tail_it->add_out_edge(&(*edge_it));
            head_it->add_in_edge(&(*edge_it));
        }
    }

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(NodeIterPair tails, NodeIterPair heads, WeightIterPair weights)
{
    int num_tails = tails.second - tails.first;
    int num_heads = heads.second - heads.first;
    int num_edges = num_tails * num_heads;

    assert(num_tails > 0 && num_heads > 0 && (weights.second - weights.first) >= num_edges);

    auto edge_it_pair = add_edges(num_edges);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weights.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it) {
        for(auto head_it = heads.first; head_it != heads.second; ++head_it, ++edge_it, ++weight_it) {
            edge_it->set_tail(&(*tail_it));
            edge_it->set_head(&(*head_it));
            edge_it->set_weight(&(*weight_it));

            weight_it->add_edge(&(*edge_it));

            tail_it->add_out_edge(&(*edge_it));
            head_it->add_in_edge(&(*edge_it));
        }
    }

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(NodeIterPair tails, Node *head)
{
    int num_tails = tails.second - tails.first;

    assert(num_tails > 0 && head);

    auto edge_it_pair = add_edges(num_tails);
    auto weight_it_pair = add_weights(num_tails);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weight_it_pair.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it, ++weight_it, ++edge_it) {
        edge_it->set_tail(&(*tail_it));
        edge_it->set_head(head);
        edge_it->set_weight(&(*weight_it));

        weight_it->add_edge(&(*edge_it));

        tail_it->add_out_edge(&(*edge_it));
        head->add_in_edge(&(*edge_it));
    }

    return edge_it_pair;
}

EdgeIterPair NeuralNet::link(NodeIterPair tails, Node *head, WeightIterPair weights)
{
    int num_tails = tails.second - tails.first;

    assert(num_tails > 0 && head && (weights.second - weights.first) >= num_tails);

    auto edge_it_pair = add_edges(num_tails);
    auto edge_it = edge_it_pair.first;
    auto weight_it = weights.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it, ++weight_it, ++edge_it) {
        edge_it->set_tail(&(*tail_it));
        edge_it->set_head(head);
        edge_it->set_weight(&(*weight_it));

        weight_it->add_edge(&(*edge_it));

        tail_it->add_out_edge(&(*edge_it));
        head->add_in_edge(&(*edge_it));
    }

    return edge_it_pair;
}

void NeuralNet::clear_node_flags()
{
    auto zero_flag = [](Node& n) { n.zero_flag(); };
    node_groups_.foreach(zero_flag);
}

void NeuralNet::init_input(const Point& input)
{
    size_t i = 0;
    for(auto it = input_iter_pair_.first; it != input_iter_pair_.second; ++it, ++i) {
        it->set_output(input[i]);
    }
}

void NeuralNet::add_out_nodes_to_queue(Node *n)
{
    for(size_t k = 0; k < n->num_out_edges(); ++k) {
        Node *n1 = n->out_edge(k)->head();
        if(!n1->test_flag(Node::FLAG_VISITED_FEED_FORWARD)) {
            queue_.push_back(n1);
            n1->set_flag(Node::FLAG_VISITED_FEED_FORWARD);
        }
    }
}

void NeuralNet::init_queue_feed_forward()
{
    queue_.clear();
    for(auto input_it = input_iter_pair_.first; input_it != input_iter_pair_.second; ++input_it) {
        add_out_nodes_to_queue(&(*input_it));
    }
}

void NeuralNet::init_feed_forward(const Point& input)
{
    init_input(input);
    clear_node_flags();
    init_queue_feed_forward();
}

void NeuralNet::feed_forward(const Point& input)
{
    init_feed_forward(input);
    while(!queue_.empty()) {
        Node *n = queue_.front();
        queue_.pop_front();

        n->feed_forward();

        add_out_nodes_to_queue(n);
    }

    output_model_->output_proc(output_iter_pair_);
}

void NeuralNet::add_in_nodes_to_queue(Node *n)
{
    for(size_t k = 0; k < n->num_in_edges(); ++k) {
        Node *n1 = n->in_edge(k)->tail();
        if(n1->num_in_edges() > 0 && !n1->test_flag(Node::FLAG_VISITED_BACK_PROP)) {
            queue_.push_back(n1);
            n1->set_flag(Node::FLAG_VISITED_BACK_PROP);
        }
    }
}

void NeuralNet::init_queue_back_prop()
{
    for(auto it = output_iter_pair_.first; it != output_iter_pair_.second; ++it) {
        add_in_nodes_to_queue(&(*it));
    }
}

void NeuralNet::init_back_prop(const Point& target)
{
    output_model_->output_err_proc(output_iter_pair_, target);
    init_queue_back_prop();
}

void NeuralNet::back_prop(const Point& target)
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
    auto add_der = [](Weight& w) { w.cal_add_der(); };

    weight_groups_.foreach(add_der);
}
