#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#include "node.hpp"
#include "weight.hpp"
#include <cassert>

class NeuralNet {
public:
    NeuralNet(unsigned int num_inputs, unsigned int num_hiddens, unsigned int num_outputs, unsigned int num_weights);

    virtual ~NeuralNet() {}

    void bind_weight(Index weight_id, Index tail_id, Index head_id);

    const Node& get_node(Index node_id) const
    {
        assert(node_id < nodes_.size());
        return nodes_[node_id];
    }

    Node& get_node(Index node_id)
    {
        assert(node_id < nodes_.size());
        return nodes_[node_id];
    }

    unsigned int num_nodes() const { return nodes_.size(); }

    unsigned int num_inputs() const { return num_inputs_; }

    unsigned int num_outputs() const { return num_outputs_; }

    std::vector<Node>::const_iterator input_begin() const { return nodes_.begin(); }

    std::vector<Node>::iterator input_begin() { return nodes_.begin(); }

    std::vector<Node>::const_iterator input_end() const { return nodes_.begin() + num_inputs_; }

    std::vector<Node>::iterator input_end() { return nodes_.begin() + num_inputs_; }

    std::vector<Node>::iterator output_begin() { return nodes_.begin(); }

    std::vector<Node>::const_iterator output_end() const { return nodes_.begin() + num_inputs_; }

    std::vector<Node>::iterator output_end() { return nodes_.begin() + num_inputs_; }

    std::vector<Node>::const_iterator nodes_begin() const { return nodes_.begin(); }

    std::vector<Node>::iterator nodes_begin() { return nodes_.begin(); }

    std::vector<Node>::const_iterator nodes_end() const { return nodes_.end(); }

    std::vector<Node>::iterator nodes_end() { return nodes_.end(); }

    const Weight& get_weight(Index weight_id) const
    {
        assert(weight_id < weights_.size());
        return weights_[weight_id];
    }

    Weight& get_weight(Index weight_id)
    {
        assert(weight_id < weights_.size());
        return weights_[weight_id];
    }

    unsigned int num_weights() const { return weights_.size(); }

    std::vector<Weight>::const_iterator weights_begin() const { return weights_.begin(); }

    std::vector<Weight>::iterator weights_begin() { return weights_.begin(); }

    std::vector<Weight>::const_iterator weights_end() const { return weights_.end(); }

    std::vector<Weight>::iterator weights_end() { return weights_.end(); }

private:
    unsigned int num_inputs_;
    unsigned int num_hiddens_;
    unsigned int num_outputs_;
    std::vector<Node> nodes_;
    std::vector<Weight> weights_;
};

#endif
