#include <cassert>
#include <cmath>
#include <cstddef>
#include "neural_net.hpp"
#include "eval.hpp"
#include "utils.hpp"

EvaluateFunc EvaluateFunc::eval_funcs[] = {
    EvaluateFunc(mean_euclid_dist, nullptr)
};

EvaluateFunc *EvaluateFunc::get_eval_func(EvaluateFuncType type)
{
    assert(type >= 0 && type < EF_COUNT);
    return &eval_funcs[type];
}

EvaluateFunc::EvaluateFunc(ErrorFunc func, const Point *param):
    eval_func_(func)
{
    if(param) {
        for(auto it = param->begin(); it != param->end(); ++it) {
            param_.push_back(*it);
        }
    }
}

double mean_euclid_dist(NeuralNet *net, const DataSet& inputs, const DataSet& targets, const Point *param)
{
    assert(inputs.size() == targets.size());

    double total_dist = 0.0;

    for(size_t i = 0; i < inputs.size(); ++i) {
        net->feed_forward(inputs[i]);

        double dist = 0.0;
        const Point& target = targets[i];

        for(size_t j = net->output_start(), k = 0; k < net->output_size(); ++j, ++k) {
            double d = net->node(j)->output() - target[k];
            dist += d * d;
        }
        dist = sqrt(dist);

        total_dist += dist;
    }

    return total_dist / static_cast<double>(inputs.size());
}
