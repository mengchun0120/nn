#ifndef __OBJ_MODEL_HPP__
#define __OBJ_MODEL_HPP__

#include <vector>

class NeuralNet;

typedef void (*OutputProc)(NeuralNet *net);
typedef double (*LossFunc)(NeuralNet *net, const std::vector<double>& target);
typedef void (*OutputErrorProc)(NeuralNet *net, const std::vector<double>& target);

class OutputModel {
    static OutputModel output_models[];
public:
    enum OutputModelType {
        OMT_REGRESSION_SQUARE_LOSS,     //0
        OMT_COUNT
    };

    static OutputModel *get_output_model(OutputModelType type);

    OutputModel(OutputProc output_proc, LossFunc loss_func, OutputErrorProc output_err_proc):
        get_output(output_proc),
        get_loss(loss_func),
        get_output_error(output_err_proc)
    {}

    OutputProc get_output;
    LossFunc get_loss;
    OutputErrorProc get_output_error;
};

void identity_output(NeuralNet *net);

double square_loss(NeuralNet *net, const std::vector<double>& target);

void square_loss_error(NeuralNet *net, const std::vector<double>& target);

#endif
