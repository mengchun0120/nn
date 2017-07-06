#include "fully_connected_net.hpp"

using namespace std;

FullyConnectedNet::FullyConnectedNet(const std::vector<size_t>& layer_sizes, ActFunc *act_func,
                                     OutputModel *output_model):
    NeuralNet(output_model)
{
    build_net(layer_sizes, act_func);
}

void FullyConnectedNet::build_net(const std::vector<size_t>& layer_sizes, ActFunc *act_func)
{
    if(layer_sizes.size() < 2) {
        throw runtime_error("Invalid layer count (must be no less than 2)");
    }

    clear();

    size_t layer;
    auto set_act_func = [&](Node& n) { n.set_act_func(act_func); };

    for(layer = 0; layer < layer_sizes.size(); ++layer) {
        if(layer_sizes[layer] == 0) {
            throw runtime_error("Invalid layer size (must be greater than zero)");
        }

        size_t node_count = (layer < layer_sizes.size() - 1) ?
                                layer_sizes[layer] + 1 : layer_sizes[layer];
        Group<Node>& nodes = add_nodes(node_count);

        if(layer > 0) {
            if(layer < layer_sizes.size() - 1) {
                Group<Node>::Range range = nodes.range(0, layer_sizes[layer]);
                for_each(range.first, range.second, set_act_func);
            }

            size_t num_edges = node_layers_[layer-1]->size() * layer_sizes[layer];

            Group<Weight>& weights = add_weights(num_edges);
            weight_layers_.push_back(&weights);

            Group<Edge>& edges = link(node_layers_[layer-1]->range(),
                                      nodes.range(0, layer_sizes[layer]),
                                      weights.range());
            edge_layers_.push_back(&edges);
        }

        node_layers_.push_back(&nodes);
    }

    set_inputs(node_layers_[0]->range(0, layer_sizes[0]));
    set_outputs(node_layers_[layer_sizes.size()-1]->range());
}
