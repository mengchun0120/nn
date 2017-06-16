#ifndef __WEIGHT_HPP__
#define __WEIGHT_HPP__

#ifndef __TYPES_HPP__
#include "types.hpp"
#endif

class Weight {
public:
    Weight(): value_(0) {}

    virtual ~Weight() {}

    double get_value() const { return value_; }

    void set_value(double new_value) { value_ = new_value; }

    void add_tail(Index node_id);

    unsigned int num_tails() const { return tails_.size(); }

    IndexVector::const_iterator tails_begin() const { return tails_.begin(); }

    IndexVector::const_iterator tails_end() const { return tails_.end(); }

    void add_head(Index node_id);

    unsigned int num_heads() const { return heads_.size(); }

    IndexVector::const_iterator heads_begin() const { return heads_.begin(); }

    IndexVector::const_iterator heads_end() const { return heads_.end(); }

    unsigned int get_flag() const { return flag_; }

private:
    double value_;
    IndexVector tails_;
    IndexVector heads_;
    unsigned int flag_;
};

#endif
