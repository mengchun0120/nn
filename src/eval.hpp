#ifndef __EVAL_HPP__
#define __EVAL_HPP__

#include <functional>

class NeuralNet;

typedef double std::function<NeuralNet *net, const DataSet& inputs, const DataSet& targets> EvaluateFunc;

class MeanEuclidDistEvaluateFunc {
public:
    double operator()(NeuralNet *net, const DataSet& inputs, const DataSet& targets);
};

#endif
