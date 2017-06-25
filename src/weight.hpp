#ifndef __WEIGHT_HPP__
#define __WEIGHT_HPP__

#include <cassert>

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

    void add_der(double v)
    {
        der_ += v;
    }

private:
    double value_;
    double der_;
};

#endif
