#ifndef __LEARN_HPP__
#define __LEARN_HPP__

#include <cassert>
#include <cstddef>

class EvaluateFunc;
class NeuralNet;

class LearnEngine {
public:
    LearnEngine(NeuralNet *net)
    {
        assert(net);
        net_ = net;
    }

    virtual ~LearnEngine()
    {}

    void learn(const DataSet& test_set, const DataSet& test_target,
               const DataSet& validate_set, const DataSet& validate_target,
               size_t batch_size, size_t num_epochs, double learn_rate, size_t exit_epochs);

private:
    NeuralNet *net_;
};

#endif
