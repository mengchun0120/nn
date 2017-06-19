#include <ctime>
#include <gsl/gsl_rng.h>
#include "neural_net.hpp"
#include "init_weight.hpp"

void random_weight(NeuralNet *net, const Point *param)
{
    assert(net && param && param->size() >= 2);

    gsl_rng_env_setup();
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    unsigned long seed = static_cast<unsigned long>(time(nullptr));
    gsl_rng_set(r, seed);

    double min = (*param)[0], max = (*param)[1];
    double k = (max - min) / (gsl_rng_max(r) - gsl_rng_min(r));
    double b = max - k * gsl_rng_max(r);

    for(size_t i = 0; i < net->num_weights(); ++i) {
        double w = k * static_cast<double>(gsl_rng_get(r)) + b;
        net->weight(i)->set_value(w);
    }
}
