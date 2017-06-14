#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <vector>

class Weight {
public:
    Weight(): value_(0) {}

    virtual ~Weight() {}

    double get_value() const { return value_; }

    void set_value(double new_value) { value_ = new_value; }

    void add_tail(unsigned int node_id);

    unsigned int num_tails() const { return tails_.size(); }

    std::vector<unsigned int>::const_iterator tails_begin() const { return tails_.begin(); }

    std::vector<unsigned int>::const_iterator tails_end() const { return tails_.end(); }

    void add_head(unsigned int node_id);

    unsigned int num_heads() const { return heads_.size(); }

    std::vector<unsigned int>::const_iterator heads_begin() const { return heads_.begin(); }

    std::vector<unsigned int>::const_iterator heads_end() const { return heads_.end(); }

    unsigned int get_flag() const { return flag_; }

private:
    double value_;
    std::vector<unsigned int> tails_;
    std::vector<unsigned int> heads_;
    unsigned int flag_;
};

#endif
