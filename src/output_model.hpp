#ifndef __OBJ_MODEL_HPP__
#define __OBJ_MODEL_HPP__

#include "types.hpp"

class NeuralNet;

typedef void (*OutputProc)(NeuralNet *net, const Point *param);
typedef double (*LossFunc)(NeuralNet *net, const Point& target, const Point *param);
typedef void (*OutputErrorProc)(NeuralNet *net, const Point& target, const Point *param);

class OutputModel {
    static OutputModel output_models[];
public:
    enum OutputModelType {
        OM_REGRESSION_SQUARE_LOSS,     //0
        OM_COUNT
    };

    static OutputModel *get_output_model(OutputModelType type);

    OutputModel(OutputProc output_proc, LossFunc loss_func, OutputErrorProc output_err_proc, const Point *param=nullptr);


    void get_output(NeuralNet *net)
    {
        get_output_(net, &param_);
    }

    double get_loss(NeuralNet *net, const Point& target)
    {
        return get_loss_(net, target, &param_);
    }

    void get_output_error(NeuralNet *net, const Point& target)
    {
        return get_output_error_(net, target, &param_);
    }

private:
    OutputProc get_output_;
    LossFunc get_loss_;
    OutputErrorProc get_output_error_;
    Point param_;
};

void identity_output(NeuralNet *net, const Point *param);

double square_loss(NeuralNet *net, const Point& target, const Point *param);

void square_loss_error(NeuralNet *net, const Point& target, const Point *param);

#endif
