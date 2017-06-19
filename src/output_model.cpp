#include <cassert>
#include "neural_net.hpp"
#include "output_model.hpp"

OutputModel OutputModel::output_models[] = {
    OutputModel(identity_output, square_loss, square_loss_error, nullptr)
};

OutputModel *OutputModel::get_output_model(OutputModelType type)
{
    assert(type >= 0 && type < OM_COUNT);
    return &output_models[type];
}

OutputModel::OutputModel(OutputProc output_proc, LossFunc loss_func,
                         OutputErrorProc output_err_proc, const Point *param):
    get_output_(output_proc),
    get_loss_(loss_func),
    get_output_error_(output_err_proc)
{
    if(param) {
        for(auto it = param->begin(); it != param->end(); ++it) {
            param_.push_back(*it);
        }
    }
}


void identity_output(NeuralNet *net, const Point *param)
{
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        Node *n = net->node(i);
        n->set_output(n->act());
    }
}

double square_loss(NeuralNet *net, const Point& target, const Point *param)
{
    assert(net->output_size() == target.size());
    double loss = 0.0;
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        double d = net->node(i)->act() - target[j];
        loss += d * d;
    }
    loss /= 2.0;
    return loss;
}

void square_loss_error(NeuralNet *net, const Point& target, const Point *param)
{
    assert(net->output_size() == target.size());
    for(size_t i = net->output_start(), j = 0; j < net->output_size(); ++i, ++j) {
        Node *n = net->node(i);
        n->set_error(n->act() - target[j]);
    }
}
