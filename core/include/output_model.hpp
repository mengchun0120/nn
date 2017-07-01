#ifndef __OBJ_MODEL_HPP__
#define __OBJ_MODEL_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

#ifndef __NODE_HPP__
#include "node.hpp"
#endif

#ifndef __GROUP_HPP__
#include "group.hpp"
#endif

typedef std::function<void(Group<Node>::Range)> OutputProc;
typedef std::function<double(Group<Node>::Range, const double *)> LossFunc;
typedef std::function<void(Group<Node>::Range, const double *)> OutputErrorProc;

class IdentityOutputProc {
public:
    void operator()(Group<Node>::Range outputs);
};

class SquareLossFunc {
public:
    double operator()(Group<Node>::Range outputs, const double *target);
};

class SquareLossErrorProc {
public:
    void operator()(Group<Node>::Range outputs, const double *target);
};

class OutputModel {
public:
    static OutputModel square_loss_regression_model()
    {
        return OutputModel(IdentityOutputProc(), SquareLossFunc(), SquareLossErrorProc());
    }

    OutputModel(OutputProc output_proc, LossFunc loss_func, OutputErrorProc output_err_proc)
    {
        this->output_proc = output_proc;
        this->loss_func = loss_func;
        this->output_err_proc = output_err_proc;
    }

    OutputProc output_proc;
    LossFunc loss_func;
    OutputErrorProc output_err_proc;
};

#endif
