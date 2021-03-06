#include <cassert>
#include <cmath>
#include <cstddef>
#include "neural_net.hpp"
#include "eval.hpp"

double EuclidDistEvaluateFunc::operator()(NeuralNet *net, const Batch& inputs, const Batch& targets)
{
    assert(net && inputs.size() == targets.size() && inputs.size() > 0);

    double total_dist = 0.0;
    auto& outputs = net->outputs();

    for(size_t i = 0; i < inputs.size(); ++i) {
        net->feed_forward(inputs[i]);

        double dist = 0.0;
        double *target = targets[i];

        for(auto output_it = outputs.first; output_it != outputs.second; ++output_it, ++target) {
            double d = output_it->output() - *target;
            dist += d * d;
        }
        dist = sqrt(dist);

        total_dist += dist;
    }

    return total_dist / static_cast<double>(inputs.size());
}
