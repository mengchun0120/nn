#ifndef __NODE_HPP__
#define __NODE_HPP__

#ifndef __TYPES_HPP__
#include "types.hpp"
#endif

class Node {
public:
    Node(): act_(0), act_der_(0) {}

    virtual ~Node() {}

    double get_act() const { return act_; }

    void set_act(double new_act) { act_ = new_act; }

    double get_act_der() const { return act_der_; }

    void set_act_der(double new_act_der) { act_der_ = new_act_der; }

    double get_output() const { return output_; }

    void set_output(double new_output) { output_ = new_output; }

    void add_in_weight(Index weight_id);

    unsigned int num_in_weights() const { return in_weights_.size(); }

    IndexVector::const_iterator in_weights_begin() const { return in_weights_.begin(); }

    IndexVector::const_iterator in_weights_end() const { return in_weights_.end(); }

    void add_out_weight(Index weight_id);

    unsigned int num_out_weights() const { return out_weights_.size(); }

    IndexVector::const_iterator out_weights_begin() const { return out_weights_.begin(); }

    IndexVector::const_iterator out_weights_end() const { return out_weights_.end(); }

    unsigned int get_flag() const { return flag_; }

private:
    double act_;
    double act_der_;
    double output_;
    IndexVector in_weights_;
    IndexVector out_weights_;
    unsigned int flag_;
};

#endif
