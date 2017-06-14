#ifndef __NEURAL_NET__
#define __NEURAL_NET__

#include "node.hpp"
#include "weight.hpp"
#include <cassert>

class NeuralNet {
public:
    NeuralNet(unsigned int num_nodes, unsigned int num_weights);

    virtual ~NeuralNet() {}

    void bind_weight(unsigned int weight_id, unsigned int tail_id, unsigned int head_id);

    const Node& get_node(unsigned int node_id) const
    {
        assert(node_id < nodes_.size());
        return nodes_[node_id];
    }

    Node& get_node(unsigned int node_id)
    {
        assert(node_id < nodes_.size());
        return nodes_[node_id];
    }

    unsigned int num_nodes() const { return nodes_.size(); }

    std::vector<Node>::const_iterator nodes_begin() const { return nodes_.begin(); }

    std::vector<Node>::iterator nodes_begin() { return nodes_.begin(); }

    std::vector<Node>::const_iterator nodes_end() const { return nodes_.end(); }

    std::vector<Node>::iterator nodes_end() { return nodes_.end(); }

    const Weight& get_weight(unsigned int weight_id) const
    {
        assert(weight_id < weights_.size());
        return weights_[weight_id];
    }

    Weight& get_weight(unsigned int weight_id)
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
    std::vector<Node> nodes_;
    std::vector<Weight> weights_;
};

#endif
