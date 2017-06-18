#ifndef __ACT_FUNC_HPP__
#define __ACT_FUNC_HPP__

class Node;

typedef double (*NodeFunc)(Node *);

class ActFunc {
    static ActFunc act_funcs[];

public:
    enum ActFuncType {
        AF_RELINEAR,
        AF_TOTAL
    };

    static ActFunc *get_act_func(ActFuncType type);

    ActFunc(NodeFunc a, NodeFunc ad): act(a), act_der(ad) {}

    NodeFunc act;
    NodeFunc act_der;
};

double relinear(Node *n);
double relinear_der(Node *n);

#endif
