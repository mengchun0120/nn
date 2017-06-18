#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#ifndef __NODE_HPP__
#include "node.hpp"
#endif

#ifndef __WEIGHT_HPP__
#include "weight.hpp"
#endif

#ifndef __EDGE_HPP__
#include "edge.hpp"
#endif

#include <cassert>
#include <cstddef>

class OutputModel;

class NeuralNet {
public:
    NeuralNet(OutputModel *output_model);

    virtual ~NeuralNet() {}

    size_t num_nodes() const { return nodes_.size(); }

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

    size_t add_node(ActFunc *act_func=nullptr);

    void set_input(size_t input_start, size_t input_size);

    size_t input_start() const { return input_start_; }

    size_t input_size() const { return input_size_; }

    void set_output(size_t output_start, size_t output_size);

    size_t output_start() const { return output_start_; }

    size_t output_size() const { return output_size_; }

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

    size_t num_weights() const { return weights_.size(); }

    size_t add_weight();

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

    size_t add_edge(size_t tail_idx, size_t head_idx, size_t weight_idx);

    size_t num_edges() const { return edges_.size(); }

private:
    std::vector<Node> nodes_;
    size_t input_start_;
    size_t input_size_;
    size_t output_start_;
    size_t output_size_;
    std::vector<Weight> weights_;
    std::vector<Edge> edges_;
    OutputModel* output_model_;
};

#endif
