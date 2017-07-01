#ifndef __EVAL_HPP__
#define __EVAL_HPP__

#include <functional>
#include "batch.hpp"

class NeuralNet;

typedef std::function<double(NeuralNet *, const Batch&, const Batch&)> EvaluateFunc;

class EuclidDistEvaluateFunc {
public:
    double operator()(NeuralNet *net, const Batch& inputs, const Batch& targets);
};

#endif
