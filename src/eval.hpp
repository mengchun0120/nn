#ifndef __EVAL_HPP__
#define __EVAL_HPP__

#include "types.hpp"
#include <functional>

class NeuralNet;

typedef std::function<double(NeuralNet *, const DataSet&, const DataSet&)> EvaluateFunc;

class EuclidDistEvaluateFunc {
public:
    double operator()(NeuralNet *net, const DataSet& inputs, const DataSet& targets);
};

#endif
