#include <cassert>
#include "act_func.hpp"
#include "output_model.hpp"
#include "neural_net.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    size_t layer_nodes[] = {2, 2, 2};
    double weights[][3][2] = {
        {{1., 2.}, {3., -1.}, {-2.8, -3.2}},
        {{4., 5.}, {6., -4.}, {2.7, 2.8}}
    };
    vector<double> input{2.5, 1.7};
    vector<double> target{1.5, 2.7};

    ActFunc act_func = ActFunc::relinear_act_func();
    OutputModel output_model = OutputModel::square_loss_regression_model();
    NeuralNet net(&output_model);

    NodeIterPair inputs = net.add_inputs(layer_nodes[0]);
    NodeIterPair biases = net.add_biases(2);
    NodeIterPair hiddens = net.add_hiddens(layer_nodes[1], &act_func);
    NodeIterPair outputs = net.add_outputs(layer_nodes[2]);
    auto bias_it = biases.first;

    EdgeIterPair edges[]{net.link(inputs, hiddens), net.link(hiddens, outputs)};
    EdgeIterPair bias_edges[2];

    bias_it->set_output(1.0);
    bias_edges[0] = net.link(&(*bias_it), hiddens);
    ++bias_it;
    bias_it->set_output(1.0);
    bias_edges[1] = net.link(&(*bias_it), outputs);

    int i, j, k;

    for(i = 0; i < 2; ++i) {
        auto edge_it = edges[i].first;
        for(j = 0; j < 2; ++j) {
            for(k = 0; k < 2; ++k, ++edge_it) {
                edge_it->weight()->set_value(weights[i][j][k]);
            }
        }

        edge_it = bias_edges[i].first;
        for(j = 0; j < 2; ++j, ++edge_it) {
            edge_it->weight()->set_value(weights[i][2][j]);
        }
    }

    // Test feed-forward.
    net.feed_forward(input);

    auto node_it = hiddens.first;

    double expected_act1[2], expected_output1[2], expected_act2[2];

    // Calculate the activation and output of the hidden layer.
    for(i = 0; i < 2; ++i, ++node_it) {
        expected_act1[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_act1[i] += weights[0][j][i] * input[j];
        }
        // Add bias.
        expected_act1[i] += weights[0][2][i];
        expected_output1[i] = expected_act1[i] > 0.0 ? expected_act1[i] : 0.0;

        assert(expected_act1[i] == node_it->act() && expected_output1[i] == node_it->output());
    }

    // Calculate the activation of the output layer
    for(i = 0, node_it = outputs.first; i < 2; ++i, ++node_it) {
        expected_act2[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_act2[i] += weights[1][j][i] * expected_output1[j];
        }
        // Add bias.
        expected_act2[i] += weights[1][2][i];

        assert(expected_act2[i] == node_it->act() && expected_act2[i] == node_it->output());
    }

    // Test back propagation
    net.back_prop(target);

    double expected_error2[2], expected_error1[2];

    // Calculate the errors of the output layer
    for(i = 0, node_it = outputs.first; i < 2; ++i, ++node_it) {
        expected_error2[i] = expected_act2[i] - target[i];

        assert(expected_error2[i] == node_it->error());
    }

    // Calculate the errors of the hidden layer
    for(i = 0, node_it = hiddens.first; i < 2; ++i, ++node_it) {
        expected_error1[i] = 0.0;
        for(j = 0; j < 2; ++j) {
            expected_error1[i] += expected_error2[j] * weights[1][i][j];
        }
        if(expected_act1[i] < 0.0) {
            expected_error1[i] = 0.0;
        }

        assert(expected_error1[i] == node_it->error());
    }
}
