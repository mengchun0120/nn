#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#include <cassert>
#include <cstddef>
#include <deque>
#include "types.hpp"
#include "node.hpp"
#include "weight.hpp"
#include "edge.hpp"
#include "group_list.hpp"

typedef GroupList<Node>::GroupIterator NodeGroupIter;
typedef GroupList<Node>::ItemIterPair NodeIterPair;
typedef GroupList<Edge>::GroupIterator EdgeGroupIter;
typedef GroupList<Edge>::ItemIterPair EdgeIterPair;
typedef GroupList<Weight>::GroupIterator WeightGroupIter;
typedef GroupList<Weight>::ItemIterPair WeightIterPair;

class OutputModel;

class NeuralNet {
public:
    NeuralNet(OutputModel * output_model);

    virtual ~NeuralNet()
    {}

    NodeIterPair add_inputs(size_t num_inputs);

    NodeIterPair get_inputs()
    {
        return input_iter_pair_;
    }

    size_t input_size() const
    {
        return input_size_;
    }

    NodeIterPair add_outputs(size_t num_outputs);

    NodeIterPair get_outputs()
    {
        return output_iter_pair_;
    }

    size_t output_size() const
    {
        return output_size_;
    }

    NodeIterPair add_biases(size_t num_biases);

    size_t num_biases() const
    {
        return num_biases_;
    }

    NodeIterPair add_hiddens(size_t num_hiddens, ActFunc *act_func);

    size_t num_hiddens() const
    {
        return num_hiddens_;
    }

    size_t num_nodes() const
    {
        return node_groups_.num_items();
    }

    NodeGroupIter node_group_begin()
    {
        return node_groups_.begin();
    }

    WeightIterPair add_weights(size_t num_weights);

    WeightGroupIter weight_group_begin()
    {
        return weight_groups_.begin();
    }

    EdgeIterPair add_edges(size_t num_edges);

    EdgeGroupIter edge_group_begin()
    {
        return edge_groups_.begin();
    }

    EdgeIterPair link(Node *tail, Node *head);

    EdgeIterPair link(Node *tail, Node *head, Weight *weight);

    EdgeIterPair link(Node *tail, NodeIterPair heads);

    EdgeIterPair link(Node *tail, NodeIterPair heads, WeightIterPair weights);

    EdgeIterPair link(NodeIterPair tails, NodeIterPair heads);

    EdgeIterPair link(NodeIterPair tails, NodeIterPair heads, WeightIterPair weights);

    EdgeIterPair link(NodeIterPair tails, Node *head);

    EdgeIterPair link(NodeIterPair tails, Node *head, WeightIterPair weights);

    void feed_forward(const Point& input);

    void back_prop(const Point& target);

    void add_gradient();

private:
    GroupList<Node> node_groups_;
    size_t input_size_;
    NodeIterPair input_iter_pair_;
    size_t output_size_;
    NodeIterPair output_iter_pair_;
    size_t num_biases_;
    size_t num_hiddens_;

    GroupList<Edge> edge_groups_;
    GroupList<Weight> weight_groups_;

    std::deque<Node *> queue_;

    OutputModel *output_model_;

    void init_input(const Point& input);

    void clear_node_flags();

    void add_out_nodes_to_queue(Node *n);

    void init_queue_feed_forward();

    void init_feed_forward(const Point& input);

    void add_in_nodes_to_queue(Node *n);

    void init_queue_back_prop();

    void init_back_prop(const Point& target);
};

#endif
