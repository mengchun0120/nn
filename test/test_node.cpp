#include <cassert>
#include "act_func.hpp"
#include "weight.hpp"
#include "edge.hpp"
#include "node.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    Node in_nodes[3], out_nodes[3];
    Weight in_weights[3], out_weights[3];
    Edge in_edges[3], out_edges[3];
    ActFunc act_func = ActFunc::relinear_act_func();
    Node n(&act_func);
    size_t i;

    for(i = 0; i < 3; ++i) {
        in_edges[i].set_tail(&in_nodes[i]);
        in_edges[i].set_head(&n);
        in_edges[i].set_weight(&in_weights[i]);
        n.add_in_edge(&in_edges[i]);

        out_edges[i].set_tail(&n);
        out_edges[i].set_head(&out_nodes[i]);
        out_edges[i].set_weight(&out_weights[i]);
        n.add_out_edge(&out_edges[i]);
    }

    double weights1[] = {1.2, -2.6, 10.0};
    double input1[] = {2.6, 3.4, 23.0};
    double expected_act = weights1[0] * input1[0] + weights1[1] * input1[1] + weights1[2] * input1[2];
    double expected_output = expected_act;

    for(i = 0; i < 3; ++i) {
        in_weights[i].set_value(weights1[i]);
        in_nodes[i].set_output(input1[i]);
    }

    n.feed_forward();
    assert(n.act() == expected_act && n.output() == expected_act &&
           n.output() == expected_output);

    double weights2[] = {1.3, -2.5, 2.6};
    double errors[] = {3.3, 2.57, 3.75};
    double expected_err = weights2[0] * errors[0] + weights2[1] * errors[1] + weights2[2] * errors[2];

    for(i = 0; i < 3; ++i) {
        out_weights[i].set_value(weights2[i]);
        out_nodes[i].set_error(errors[i]);
    }

    n.back_prop();

    assert(n.error() == expected_err);
}
