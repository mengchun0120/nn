#ifndef __WEIGHT_HPP__
#define __WEIGHT_HPP__

#include <vector>

class Edge;

class Weight {
public:
    Weight(): value_(0.0), der_(0.0) {}

    virtual ~Weight() {}

    double value() const { return value_; }

    void set_value(double new_value) { value_ = new_value; }

    std::vector<Edge *>::const_iterator edges_begin() const { return edges_.begin(); }

    std::vector<Edge *>::iterator edges_begin() { return edges_.begin(); }

    std::vector<Edge *>::const_iterator edges_end() const { return edges_.end(); }

    std::vector<Edge *>::iterator edges_end() { return edges_.end(); }

    void add_edge(Edge *e);

    double der() const { return der_; }

    double cal_der();

private:
    double value_;
    double der_;
    std::vector<Edge *> edges_;
};

#endif
