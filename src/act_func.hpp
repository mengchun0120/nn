#ifndef __ACT_FUNC_HPP__
#define __ACT_FUNC_HPP__

typedef double (*ScalarFunc)(double);

struct ActFunc {
    ActFunc(ScalarFunc a, ScalarFunc ad): act(a), act_der(ad) {}
    ScalarFunc act;
    ScalarFunc act_der;
};

enum ActFuncTypes {
    AF_RELINEAR,
    AF_TOTAL
};

extern const ActFunc g_act_funcs[];

double relinear(double x);

double relinear_der(double x);

#endif
