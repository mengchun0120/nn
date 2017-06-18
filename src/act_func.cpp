#include <cassert>
#include "node.hpp"
#include "act_func.hpp"

ActFunc ActFunc::act_funcs[] = {
    ActFunc(relinear, relinear_der)
};

ActFunc *ActFunc::get_act_func(ActFuncType type)
{
    assert(type >= 0 && type < AF_TOTAL);
    return &act_funcs[type];
}

double relinear(Node *n)
{
    return (n->output() > 0.0) ? n->output() : 0.0;
}

double relinear_der(Node *n)
{
    return (n->output() >= 0.0) ? 1.0 : 0.0;
}
