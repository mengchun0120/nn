#ifndef __ACT_FUNC_HPP__
#define __ACT_FUNC_HPP__

#include <functional>

class Node;
typedef std::function<double(Node *)> ActivationFunc;

class RelinearActivation {
public:
    double operator()(Node *n);
};

class RelinearDerivative {
public:
    double operator()(Node *n);
};

class ActFunc {
public:
    static ActFunc relinear_act_func()
    {
        return ActFunc(RelinearActivation(), RelinearDerivative());
    }

    ActFunc(ActivationFunc a, ActivationFunc ad):
        act(a), act_der(ad)
    {}

    ActivationFunc act;
    ActivationFunc act_der;
};

#endif
