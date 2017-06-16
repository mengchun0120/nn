#include "act_func.hpp"

const ActFunc g_act_funcs[] = {
    ActFunc(relinear, relinear_der)
};

double relinear(double x)
{
    return (x > 0.0) ? x : 0.0;
}

double relinear_der(double x)
{
    return (x >= 0.0) ? 1 : 0.0;
}
