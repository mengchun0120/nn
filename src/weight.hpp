#ifndef __WEIGHT_HPP__
#define __WEIGHT_HPP__

#include <cassert>
#include <cstddef>
#include <vector>

class Edge;

class Weight {
public:
    Weight():
        value_(0.0),
        der_(0.0)
    {}

    virtual ~Weight()
    {}

    double value() const
    {
        return value_;
    }

    void set_value(double new_value)
    {
        value_ = new_value;
    }

    double der() const
    {
        return der_;
    }

    void set_der(double new_value)
    {
        der_ = new_value;
    }

    double cal_der();

    void add_edge(Edge *e)
    {
        edges_.push_back(e);
    }

    const Edge *edge(size_t idx) const
    {
        assert(idx < edges_.size());
        return edges_[idx];
    }

    Edge *edge(size_t idx)
    {
        assert(idx < edges_.size());
        return edges_[idx];
    }

    size_t num_edges() const
    {
        return edges_.size();
    }

    void cal_add_der()
    {
        der_ += cal_der();
    }

private:
    double value_;
    double der_;
    std::vector<Edge *> edges_;
};

#endif
