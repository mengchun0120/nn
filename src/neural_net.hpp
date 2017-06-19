#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#include <cassert>
#include <cstddef>
#include <deque>
#include "node.hpp"
#include "weight.hpp"
#include "edge.hpp"

class OutputModel;

class NeuralNet {
    enum Stage {
        STAGE_FEED_FORWARD = 1,
        STAGE_BACK_PROP
    };
public:
    NeuralNet(size_t num_nodes, size_t num_edges, size_t num_weights, OutputModel *output_model);

    virtual ~NeuralNet()
    {}

    size_t num_nodes() const
    {
        return nodes_.size();
    }

    const Node *node(size_t idx) const
    {
        assert(idx < nodes_.size());
        return &nodes_[idx];
    }

    Node *node(size_t idx)
    {
        assert(idx < nodes_.size());
        return &nodes_[idx];
    }

    void set_input(size_t input_start, size_t input_size);

    size_t input_start() const
    {
        return input_start_;
    }

    size_t input_size() const
    {
        return input_size_;
    }

    void set_output(size_t output_start, size_t output_size);

    size_t output_start() const
    {
        return output_start_;
    }

    size_t output_size() const
    {
        return output_size_;
    }

    const Weight* weight(size_t idx) const
    {
        assert(idx < weights_.size());
        return &weights_[idx];
    }

    Weight *weight(size_t idx)
    {
        assert(idx < weights_.size());
        return &weights_[idx];
    }

    size_t num_weights() const
    {
        return weights_.size();
    }

    const Edge *edge(size_t idx) const
    {
        assert(idx < edges_.size());
        return &edges_[idx];
    }

    Edge *edge(size_t idx)
    {
        assert(idx < edges_.size());
        return &edges_[idx];
    }

    size_t num_edges() const
    {
        return edges_.size();
    }

    void bind_edge(size_t edge_idx, size_t tail_idx, size_t head_idx, size_t weight_idx);

    double feed_forward(const std::vector<double>& input, const std::vector<double>& target);

    void back_prop(const std::vector<double>& target);

    void add_gradient();

private:
    std::vector<Node> nodes_;
    std::vector<Weight> weights_;
    std::vector<Edge> edges_;
    size_t input_start_;
    size_t input_size_;
    size_t output_start_;
    size_t output_size_;
    OutputModel* output_model_;
    std::deque<Node *> queue_;

    void init_input(const std::vector<double>& input);

    void clear_node_flags();

    void add_out_nodes_to_queue(Node *n);

    void init_queue_feed_forward();

    void init_feed_forward(const std::vector<double>& input);

    void add_in_nodes_to_queue(Node *n);

    void init_queue_back_prop();

    void init_back_prop(const std::vector<double>& target);
};

#endif
