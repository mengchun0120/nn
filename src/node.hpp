#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node {
public:
    Node(): act_(0), act_der_(0) {}

    virtual ~Node() {}

    double get_act() const { return act_; }

    void set_act(double new_act) { act_ = new_act; }

    double get_act_der() const { return act_der_; }

    void set_act_der(double new_act_der) { act_der_ = new_act_der; }

    void add_in_weight(unsigned int weight_id);

    unsigned int num_in_weights() const { return in_weights_.size(); }

    std::vector<unsigned int>::const_iterator in_weights_begin() const { return in_weights_.begin(); }

    std::vector<unsigned int>::const_iterator in_weights_end() const { return in_weights_.end(); }

    void add_out_weight(unsigned int weight_id);

    unsigned int num_out_weights() const { return out_weights_.size(); }

    std::vector<unsigned int>::const_iterator out_weights_begin() const { return out_weights_.begin(); }

    std::vector<unsigned int>::const_iterator out_weights_end() const { return out_weights_.end(); }

    unsigned int get_flag() const { return flag_; }

private:
    double act_;
    double act_der_;
    std::vector<unsigned int> in_weights_;
    std::vector<unsigned int> out_weights_;
    unsigned int flag_;
};

#endif
