#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

#ifndef __NODE_HPP__
#include "node.hpp"
#endif

#ifndef __EDGE_HPP__
#include "edge.hpp"
#endif

#ifndef __WEIGHT_HPP__
#include "weight.hpp"
#endif

#ifndef __GROUP_LIST_HPP__
#include "group_list.hpp"
#endif

class OutputModel;

class NeuralNet {
public:
    NeuralNet(OutputModel * output_model);

    virtual ~NeuralNet()
    {}

    void set_inputs(const Group<Node>::Range& r)
    {
        inputs_ = r;
    }

    Group<Node>::Range& inputs()
    {
        return inputs_;
    }

    size_t input_size() const
    {
        return Group<Node>::size(inputs_);
    }

    void set_outputs(const Group<Node>::Range& r)
    {
        outputs_ = r;
    }

    Group<Node>::Range& outputs()
    {
        return outputs_;
    }

    size_t output_size() const
    {
        return Group<Node>::size(outputs_);
    }

    Group<Node>& add_nodes(size_t num_nodes, ActFunc *act_func=nullptr);

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

    void clear();

protected:
    GroupList<Node> node_groups_;
    Group<Node>::Range inputs_;
    Group<Node>::Range outputs_;

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
