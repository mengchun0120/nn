#include <cassert>
#include "neural_net.hpp"
#include "output_model.hpp"

OutputModel OutputModel::output_models[] = {
    OutputModel(identity_output, square_loss, square_loss_error)
};

OutputModel *OutputModel::get_output_model(OutputModelType type)
{
    assert(type >= 0 && type < OMT_COUNT);
    return &output_models[type];
}

void identity_output(NeuralNet *net)
{
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        Node *n = net->node(i);
        n->set_output(n->act());
    }
}

double square_loss(NeuralNet *net, const std::vector<double>& target)
{
    assert(net->output_size() == target.size());
    double loss = 0.0;
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        double d = net->node(i)->output() - target[j];
        loss += d * d;
    }
    loss /= 2.0;
    return loss;
}

void square_loss_error(NeuralNet *net, const std::vector<double>& target)
{
    assert(net->output_size() == target.size());
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        Node *n = net->node(i);
        n->set_error(n->act() - target[j]);
    }
}
