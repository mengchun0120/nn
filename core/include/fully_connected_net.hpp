#ifndef __FULLY_CONNECTED_NET_HPP__
#define __FULLY_CONNECTED_NET_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

#ifndef __NEURAL_NET_HPP__
#include "neural_net.hpp"
#endif

class FullyConnectedNet: public NeuralNet {
public:
    FullyConnectedNet(const std::vector<size_t>& layer_sizes, ActFunc *act_func, OutputModel *output_model);

    ~FullyConnectedNet()
    {}

    void build_net(const std::vector<size_t>& layer_sizes, ActFunc *act_func);

    size_t node_layer_count() const
    {
        return node_layers_.size();
    }

    size_t edge_layer_count() const
    {
        return edge_layers_.size();
    }

    size_t weight_layer_count() const
    {
        return weight_layers_.size();
    }

    Group<Node> *node_layer(size_t layer)
    {
        assert(layer < node_layers_.size());
        return node_layers_[layer];
    }

    Group<Edge> *edge_layer(size_t layer)
    {
        assert(layer < edge_layers_.size());
        return edge_layers_[layer];
    }

    Group<Weight> *weight_layer(size_t layer)
    {
        assert(layer < weight_layers_.size());
        return weight_layers_[layer];
    }

    Node *bias(size_t layer)
    {
        assert(layer < node_layers_.size() - 2);
        return &(node_layers_[layer]->back());
    }

protected:
    std::vector<Group<Node> *> node_layers_;
    std::vector<Group<Edge> *> edge_layers_;
    std::vector<Group<Weight> *> weight_layers_;
};

#endif
