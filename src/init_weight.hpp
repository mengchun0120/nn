#ifndef __INIT_WEIGHT_HPP__
#define __INIT_WEIGHT_HPP__

#include "types.hpp"

class NeuralNet;

typedef void (*WeightInitFunc)(NeuralNet *net, const Point *param);

void random_weight(NeuralNet *net, const Point *param);

#endif
