#include <cassert>
#include "act_func.hpp"
#include "output_model.hpp"
#include "neural_net.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    size_t layer_nodes[] = {2, 2, 2};
    size_t num_nodes = layer_nodes[0] + layer_nodes[1] + layer_nodes[2] + 1;
    size_t bias_idx = 0;
    size_t layer_start[] = {1, 1+layer_nodes[0], 1+layer_nodes[0]+layer_nodes[1]};
    size_t num_edges = (layer_nodes[0] + 1) * layer_nodes[1] + (layer_nodes[1] + 1) * layer_nodes[2];
    size_t num_weights = num_edges;
    OutputModel *model = OutputModel::get_output_model(OutputModel::OM_REGRESSION_SQUARE_LOSS);
    ActFunc *act_func = ActFunc::get_act_func(ActFunc::AF_RELINEAR);
    NeuralNet net(num_nodes, num_edges, num_weights, model);
    double weights[][3][2] = {
        {{1., 2.}, {3., -1.}, {-2.8, -3.2}},
        {{4., 5.}, {6., -4.}, {2.7, 2.8}}
    };
    vector<double> input{2.5, 1.7};
    vector<double> target{1.5, 2.7};

    net.set_input(layer_start[0], layer_nodes[0]);
    net.set_output(layer_start[2], layer_nodes[2]);

    size_t i, j, layer, tail_idx, head_idx, e_idx = 0;

    // Fix bias to 1.0.
    net.node(0)->set_output(1.0);

    // Initialize activition function.
    for(i = layer_start[1], j = 0; j < layer_nodes[1]; ++j, ++i) {
        net.node(i)->set_act_func(act_func);
    }

    // Link nodes and set weights.
    for(layer = 0; layer < 2; ++layer) {
        // Link nodes from the current layer to the next layer.
        for(tail_idx = layer_start[layer], i = 0; i < layer_nodes[layer]; ++i, ++tail_idx) {
            for(head_idx = layer_start[layer+1], j = 0; j < layer_nodes[layer+1]; ++j, ++head_idx) {
                net.bind_edge(e_idx, tail_idx, head_idx, e_idx);
                net.weight(e_idx)->set_value(weights[layer][i][j]);
                ++e_idx;
            }
        }

        // Link nodes from bias node to the next layer.
        for(head_idx = layer_start[layer+1], i = 0; i < layer_nodes[layer+1]; ++i, ++head_idx) {
            net.bind_edge(e_idx, bias_idx, head_idx, e_idx);
            net.weight(e_idx)->set_value(weights[layer][2][i]);
            ++e_idx;
        }
    }

    // Test feed-forward.
    double loss = net.feed_forward(input, target);

    double expected_act1[2], expected_output1[2], expected_act2[2];

    // Calculate the activation and output of the hidden layer.
    for(i = 0; i < 2; ++i) {
        expected_act1[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_act1[i] += weights[0][j][i] * input[j];
        }
        // Add bias.
        expected_act1[i] += weights[0][2][i];
        expected_output1[i] = expected_act1[i] > 0.0 ? expected_act1[i] : 0.0;
    }

    assert(expected_act1[0] == net.node(layer_start[1])->act());
    assert(expected_act1[1] == net.node(layer_start[1]+1)->act());
    assert(expected_output1[0] == net.node(layer_start[1])->output());
    assert(expected_output1[1] == net.node(layer_start[1]+1)->output());

    // Calculate the activation of the output layer
    for(i = 0; i < 2; ++i) {
        expected_act2[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_act2[i] += weights[1][j][i] * expected_output1[j];
        }
        // Add bias.
        expected_act2[i] += weights[1][2][i];
    }

    assert(expected_act2[0] == net.node(layer_start[2])->act());
    assert(expected_act2[1] == net.node(layer_start[2]+1)->act());
    assert(expected_act2[0] == net.node(layer_start[2])->output());
    assert(expected_act2[1] == net.node(layer_start[2]+1)->output());

    double expected_loss = ((expected_act2[0] - target[0]) * (expected_act2[0] - target[0]) +
                            (expected_act2[1] - target[1]) * (expected_act2[1] - target[1])) / 2.0;
    assert(expected_loss == loss);

    net.back_prop(target);

    double expected_error2[2], expected_error1[2];

    // Calculate the errors of the output layer
    for(i = 0; i < 2; ++i) {
        expected_error2[i] = expected_act2[i] - target[i];
    }

    assert(expected_error2[0] == net.node(layer_start[2])->error());
    assert(expected_error2[1] == net.node(layer_start[2]+1)->error());

    // Calculate the errors of the hidden layer
    for(i = 0; i < 2; ++i) {
        expected_error1[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_error1[i] += expected_error2[j] * weights[1][i][j];
        }
        if(expected_act1[i] < 0.0) {
            expected_error1[i] = 0.0;
        }
    }

    assert(expected_error1[0] == net.node(layer_start[1])->error());
    assert(expected_error1[1] == net.node(layer_start[1]+1)->error());
}
