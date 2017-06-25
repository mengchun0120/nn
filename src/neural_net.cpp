#include "neural_net.hpp"
#include "output_model.hpp"
#include <iostream>

using namespace std;

NeuralNet::NeuralNet(OutputModel *output_model):
    num_biases_(0),
    num_hiddens_(0),
    output_model_(output_model)
{

}

Group<Node>& NeuralNet::add_inputs(size_t num_inputs)
{
    auto& g = node_groups_.add(num_inputs);
    inputs_ = &g;
    return g;
}

Group<Node>& NeuralNet::add_outputs(size_t num_outputs)
{
    auto& g = node_groups_.add(num_outputs);
    outputs_ = &g;
    return g;
}

Group<Node>& NeuralNet::add_biases(size_t num_biases)
{
    auto& g = node_groups_.add(num_biases);
    num_biases_ += num_biases;
    return g;
}

Group<Node>& NeuralNet::add_hiddens(size_t num_hiddens, ActFunc *act_func)
{
    auto& g = node_groups_.add(num_hiddens);
    for(auto it = g.begin(); it != g.end(); ++it) {
        it->set_act_func(act_func);
    }
    num_hiddens_ += num_hiddens;
    return g;
}

Group<Weight>& NeuralNet::add_weights(size_t num_weights)
{
    return weight_groups_.add(num_weights);
}

Group<Edge>& NeuralNet::add_edges(size_t num_edges)
{
    return edge_groups_.add(num_edges);
}

Group<Edge>& NeuralNet::link(Node *tail, Node *head)
{
    Group<Weight>& weights = add_weights(1);
    return link(tail, head, &weights[0]);
}

Group<Edge>& NeuralNet::link(Node *tail, Node *head, Weight *weight)
{
    assert(tail && head && weight);

    Group<Edge>& edges = add_edges(1);
    Edge *edge = &edges[0];

    edge->set_tail(tail);
    edge->set_head(head);
    edge->set_weight(weight);

    tail->add_out_edge(edge);
    head->add_in_edge(edge);

    return edges;
}

Group<Edge>& NeuralNet::link(Node *tail, Group<Node>::Range heads)
{
    size_t num_heads = Group<Node>::size(heads);

    assert(tail && num_heads > 0);

    Group<Edge>& edges = add_edges(num_heads);
    Group<Weight>& weights = add_weights(num_heads);
    auto edge_it = edges.begin();
    auto weight_it = weights.begin();

    for(auto node_it = heads.first; node_it != heads.second; ++node_it, ++edge_it, ++weight_it) {
        edge_it->set_tail(tail);
        edge_it->set_head(&(*node_it));
        edge_it->set_weight(&(*weight_it));

        tail->add_out_edge(&(*edge_it));
        node_it->add_in_edge(&(*edge_it));
    }

    return edges;
}

Group<Edge>& NeuralNet::link(Node *tail, Group<Node>::Range heads, Group<Weight>::Range weights)
{
    size_t num_heads = Group<Node>::size(heads);

    assert(tail && num_heads > 0 && Group<Weight>::size(weights) >= num_heads);

    Group<Edge>& edges = add_edges(num_heads);
    auto edge_it = edges.begin();
    auto weight_it = weights.first;

    for(auto node_it = heads.first; node_it != heads.second; ++node_it, ++edge_it, ++weight_it) {
        edge_it->set_tail(tail);
        edge_it->set_head(&(*node_it));
        edge_it->set_weight(&(*weight_it));

        tail->add_out_edge(&(*edge_it));
        node_it->add_in_edge(&(*edge_it));
    }

    return edges;
}

Group<Edge>& NeuralNet::link(Group<Node>::Range tails, Group<Node>::Range heads)
{
    size_t num_tails = Group<Node>::size(tails);
    size_t num_heads = Group<Node>::size(heads);

    assert(num_tails > 0 && num_heads > 0);

    size_t num_edges = num_tails * num_heads;
    Group<Edge>& edges = add_edges(num_edges);
    Group<Weight>& weights = add_weights(num_edges);
    auto edge_it = edges.begin();
    auto weight_it = weights.begin();

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it) {
        for(auto head_it = heads.first; head_it != heads.second; ++head_it, ++edge_it, ++weight_it) {
            edge_it->set_tail(&(*tail_it));
            edge_it->set_head(&(*head_it));
            edge_it->set_weight(&(*weight_it));

            tail_it->add_out_edge(&(*edge_it));
            head_it->add_in_edge(&(*edge_it));
        }
    }

    return edges;
}

Group<Edge>& NeuralNet::link(Group<Node>::Range tails, Group<Node>::Range heads, Group<Weight>::Range weights)
{
    size_t num_tails = Group<Node>::size(tails);
    size_t num_heads = Group<Node>::size(heads);
    size_t num_edges = num_tails * num_heads;

    assert(num_edges > 0 && Group<Weight>::size(weights) >= num_edges);

    Group<Edge>& edges = add_edges(num_edges);
    auto edge_it = edges.begin();
    auto weight_it = weights.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it) {
        for(auto head_it = heads.first; head_it != heads.second; ++head_it, ++edge_it, ++weight_it) {
            edge_it->set_tail(&(*tail_it));
            edge_it->set_head(&(*head_it));
            edge_it->set_weight(&(*weight_it));

            tail_it->add_out_edge(&(*edge_it));
            head_it->add_in_edge(&(*edge_it));
        }
    }

    return edges;
}

Group<Edge>& NeuralNet::link(Group<Node>::Range tails, Node *head)
{
    int num_tails = Group<Node>::size(tails);

    assert(num_tails > 0 && head);

    Group<Edge>& edges = add_edges(num_tails);
    Group<Weight>& weights = add_weights(num_tails);
    auto edge_it = edges.begin();
    auto weight_it = weights.begin();

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it, ++weight_it, ++edge_it) {
        edge_it->set_tail(&(*tail_it));
        edge_it->set_head(head);
        edge_it->set_weight(&(*weight_it));

        tail_it->add_out_edge(&(*edge_it));
        head->add_in_edge(&(*edge_it));
    }

    return edges;
}

Group<Edge>& NeuralNet::link(Group<Node>::Range tails, Node *head, Group<Weight>::Range weights)
{
    size_t num_tails = Group<Node>::size(tails);

    assert(num_tails > 0 && head && Group<Weight>::size(weights) >= num_tails);

    Group<Edge>& edges = add_edges(num_tails);
    auto edge_it = edges.begin();
    auto weight_it = weights.first;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it, ++weight_it, ++edge_it) {
        edge_it->set_tail(&(*tail_it));
        edge_it->set_head(head);
        edge_it->set_weight(&(*weight_it));

        tail_it->add_out_edge(&(*edge_it));
        head->add_in_edge(&(*edge_it));
    }

    return edges;
}

void NeuralNet::clear_node_flags()
{
    static auto zero_flag = [](Node& n) { n.zero_flag(); };
    node_groups_.foreach(zero_flag);
}

void NeuralNet::init_input(const Point& input)
{
    size_t i = 0;
    for(auto it = inputs_->begin(); it != inputs_->end(); ++it, ++i) {
        it->set_output(input[i]);
    }
}

void NeuralNet::zero_gradient()
{
    static auto zero_der = [](Weight& w) { w.set_der(0.0); };
    weight_groups_.foreach(zero_der);
}

void NeuralNet::add_out_nodes_to_queue(Node *n)
{
    for(auto it = n->out_edge_begin(); it != n->out_edge_end(); ++it) {
        Node *n1 = (*it)->head();
        if(!n1->test_flag(Node::FLAG_VISITED_FEED_FORWARD)) {
            queue_.push_back(n1);
            n1->set_flag(Node::FLAG_VISITED_FEED_FORWARD);
        }
    }
}

void NeuralNet::init_queue_feed_forward()
{
    queue_.clear();
    for(auto input_it = inputs_->begin(); input_it != inputs_->end(); ++input_it) {
        add_out_nodes_to_queue(&(*input_it));
    }
}

void NeuralNet::init_feed_forward(const Point& input)
{
    init_input(input);
    clear_node_flags();
    zero_gradient();
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

    output_model_->output_proc(outputs_->range());
}

void NeuralNet::add_in_nodes_to_queue(Node *n)
{
    for(auto it = n->in_edge_begin(); it != n->in_edge_end(); ++it) {
        Node *n1 = (*it)->tail();
        if(n1->num_in_edges() > 0 && !n1->test_flag(Node::FLAG_VISITED_BACK_PROP)) {
            queue_.push_back(n1);
            n1->set_flag(Node::FLAG_VISITED_BACK_PROP);
        }
    }
}

void NeuralNet::init_queue_back_prop()
{
    for(auto it = outputs_->begin(); it != outputs_->end(); ++it) {
        add_in_nodes_to_queue(&(*it));
    }
}

void NeuralNet::init_back_prop(const Point& target)
{
    output_model_->output_err_proc(outputs_->range(), target);
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
    static auto add_der = [](Edge& e) { e.cal_add_der(); };
    edge_groups_.foreach(add_der);
}
