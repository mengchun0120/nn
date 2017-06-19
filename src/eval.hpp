#ifndef __EVAL_HPP__
#define __EVAL_HPP__

#include "learn.hpp"

class NeuralNet;

typedef double (*ErrorFunc)(NeuralNet *net, const DataSet& inputs, const DataSet& targets, const Point *param);

class EvaluateFunc {
    static EvaluateFunc eval_funcs[];
public:
    enum EvaluateFuncType {
        EF_MEAN_EUCLIDEAN_DIST,
        EF_COUNT
    };

    static EvaluateFunc* get_eval_func(EvaluateFuncType type);

    EvaluateFunc(ErrorFunc func, const Point *param);

    double eval(NeuralNet *net, const DataSet& inputs, const DataSet& targets)
    {
        return eval_func_(net, inputs, targets, &param_);
    }

private:
    ErrorFunc eval_func_;
    Point param_;
};

double mean_euclid_dist(NeuralNet *net, const DataSet& inputs, const DataSet& targets, const Point *param);

#endif
