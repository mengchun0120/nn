#include "act_func.hpp"
#include "node.hpp"

double RelinearActivation::operator()(Node *n)
{
    return (n->act() > 0.0) ? n->act() : 0.0;
}

double RelinearDerivative::operator()(Node *n)
{
    return (n->act() >= 0.0) ? 1.0 : 0.0;
}
