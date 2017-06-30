#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#include <cassert>
#include <cstddef>
#include <deque>
#include "node.hpp"
#include "weight.hpp"
#include "edge.hpp"
#include "group_list.hpp"

class OutputModel;

class NeuralNet {
public:
    NeuralNet(OutputModel * output_model);

    virtual ~NeuralNet()
    {}

    Group<Node>& add_inputs(size_t num_inputs);

    Group<Node>& get_inputs()
    {
        return *inputs_;
    }

    size_t input_size() const
    {
        return inputs_->size();
    }

    Group<Node>& add_outputs(size_t num_outputs);

    Group<Node>& get_outputs()
    {
        return *outputs_;
    }

    size_t output_size() const
    {
        return outputs_->size();
    }

    Group<Node>& add_biases(size_t num_biases);

    size_t num_biases() const
    {
        return num_biases_;
    }

    Group<Node>& add_hiddens(size_t num_hiddens, ActFunc *act_func);

    size_t num_hiddens() const
    {
        return num_hiddens_;
    }

    size_t num_nodes() const
    {
        return node_groups_.num_items();
    }

    GroupList<Node>::Iterator node_group_begin()
    {
        return node_groups_.begin();
    }

    GroupList<Node>::ConstIterator node_group_begin() const
    {
        return node_groups_.begin();
    }

    GroupList<Node>::Iterator node_group_end()
    {
        return node_groups_.end();
    }

    GroupList<Node>::ConstIterator node_group_end() const
    {
        return node_groups_.end();
    }

    Group<Weight>& add_weights(size_t num_weights);

    size_t num_weights() const
    {
        return weight_groups_.num_items();
    }

    GroupList<Weight>::Iterator weight_group_begin()
    {
        return weight_groups_.begin();
    }

    GroupList<Weight>::ConstIterator weight_group_begin() const
    {
        return weight_groups_.begin();
    }

    GroupList<Weight>::Iterator weight_group_end()
    {
        return weight_groups_.end();
    }

    GroupList<Weight>::ConstIterator weight_group_end() const
    {
        return weight_groups_.end();
    }

    Group<Edge>& add_edges(size_t num_edges);

    size_t num_edges() const
    {
        return edge_groups_.num_items();
    }

    GroupList<Edge>::Iterator edge_group_begin()
    {
        return edge_groups_.begin();
    }

    GroupList<Edge>::ConstIterator edge_group_begin() const
    {
        return edge_groups_.begin();
    }

    GroupList<Edge>::Iterator edge_group_end()
    {
        return edge_groups_.end();
    }

    GroupList<Edge>::ConstIterator edge_group_end() const
    {
        return edge_groups_.end();
    }

    Group<Edge>& link(Node *tail, Node *head);

    Group<Edge>& link(Node *tail, Node *head, Weight *weight);

    Group<Edge>& link(Node *tail, Group<Node>::Range heads);

    Group<Edge>& link(Node *tail, Group<Node>::Range heads, Group<Weight>::Range weights);

    Group<Edge>& link(Group<Node>::Range tails, Group<Node>::Range heads);

    Group<Edge>& link(Group<Node>::Range tails, Group<Node>::Range heads, Group<Weight>::Range weights);

    Group<Edge>& link(Group<Node>::Range tails, Node *head);

    Group<Edge>& link(Group<Node>::Range tails, Node *head, Group<Weight>::Range weights);

    void feed_forward(const double* input);

    void back_prop(const double* target);

    void add_gradient();

    void foreach_node(std::function<void(Node&)> f)
    {
        node_groups_.foreach(f);
    }

    void foreach_edge(std::function<void(Edge&)> f)
    {
        edge_groups_.foreach(f);
    }

    void foreach_weight(std::function<void(Weight&)> f)
    {
        weight_groups_.foreach(f);
    }

    void zero_gradient();

private:
    GroupList<Node> node_groups_;
    Group<Node> *inputs_;
    Group<Node> *outputs_;
    size_t num_biases_;
    size_t num_hiddens_;

    GroupList<Edge> edge_groups_;
    GroupList<Weight> weight_groups_;

    std::deque<Node *> queue_;

    OutputModel *output_model_;

    void init_input(const double *input);

    void clear_node_flags();

    void add_out_nodes_to_queue(Node *n);

    void init_queue_feed_forward();

    void init_feed_forward(const double *input);

    void add_in_nodes_to_queue(Node *n);

    void init_queue_back_prop();

    void init_back_prop(const double *target);
};

#endif
