#include <cassert>
#include <cmath>
#include <cstddef>
#include "neural_net.hpp"
#include "eval.hpp"

double EuclidDistEvaluateFunc::operator()(NeuralNet *net, const DataSet& inputs, const DataSet& targets)
{
    assert(net && inputs.size() == targets.size() && inputs.size() > 0);

    double total_dist = 0.0;
    Group<Node>& outputs = net->get_outputs();

    for(size_t i = 0; i < inputs.size(); ++i) {
        net->feed_forward(inputs[i]);

        double dist = 0.0;
        auto output_it = outputs.begin();
        auto target_it = targets[i].begin();

        for(; output_it != outputs.end(); ++output_it, ++target_it) {
            double d = output_it->output() - *target_it;
            dist += d * d;
        }
        dist = sqrt(dist);

        total_dist += dist;
    }

    return total_dist / static_cast<double>(inputs.size());
}
