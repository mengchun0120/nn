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
    Group<Node>& inputs = net.add_inputs(layer_nodes[0]);
    Group<Node>& biases = net.add_biases(2);
    Group<Node>& hiddens = net.add_hiddens(layer_nodes[1], &act_func);
    Group<Node>& outputs = net.add_outputs(layer_nodes[2]);

    Group<Edge> *edges[] = {&net.link(inputs.range(), hiddens.range()), &net.link(hiddens.range(), outputs.range())};
    Group<Edge> *bias_edges[] = {&net.link(&biases[0], hiddens.range()),
                                 &net.link(&biases[1], outputs.range())};
    int i, j, k;

    biases[0].set_output(1.0);
    biases[1].set_output(1.0);

    for(i = 0; i < 2; ++i) {
        auto edge_it = edges[i]->begin();
        for(j = 0; j < 2; ++j) {
            for(k = 0; k < 2; ++k, ++edge_it) {
                edge_it->weight()->set_value(weights[i][j][k]);
            }
        }

        edge_it = bias_edges[i]->begin();
        for(j = 0; j < 2; ++j, ++edge_it) {
            edge_it->weight()->set_value(weights[i][2][j]);
        }
    }

    // Test feed-forward.
    net.feed_forward(input);

    auto node_it = hiddens.begin();
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
    for(i = 0, node_it = outputs.begin(); i < 2; ++i, ++node_it) {
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
    for(i = 0, node_it = outputs.begin(); i < 2; ++i, ++node_it) {
        expected_error2[i] = expected_act2[i] - target[i];

        assert(expected_error2[i] == node_it->error());
    }

    // Calculate the errors of the hidden layer
    for(i = 0, node_it = hiddens.begin(); i < 2; ++i, ++node_it) {
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
