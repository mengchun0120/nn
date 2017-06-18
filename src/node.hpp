#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <cassert>
#include <cstddef>
#include <vector>

class Edge;
class ActFunc;

class Node {
public:
    Node(ActFunc *act_func=nullptr);

    virtual ~Node() {}

    double act() const { return act_; }

    void set_act(double new_act) { act_ = new_act; }

    double output() const { return output_; }

    void set_output(double new_output) { output_ = new_output; }

    double act_der() const { return act_der_; }

    void set_act_der(double new_act_der) { act_der_ = new_act_der; }

    double error() const { return error_; }

    void set_error(double new_error) { error_ = new_error; }

    ActFunc *get_act_func() { return act_func_; }

    void set_act_func(ActFunc *act_func) { act_func_ = act_func; }

    const Edge *in_edge(size_t idx) const
    {
        assert(idx < in_edges_.size());
        return in_edges_[idx];
    }

    Edge *in_edge(size_t idx)
    {
        assert(idx < in_edges_.size());
        return in_edges_[idx];
    }

    size_t num_in_edges() const { return in_edges_.size(); }

    Edge *find_in_edge(Node *tail, Node *head);

    void add_in_edge(Edge *e);

    const Edge *out_edge(size_t idx) const
    {
        assert(idx < out_edges_.size());
        return out_edges_[idx];
    }

    Edge *out_edge(size_t idx)
    {
        assert(idx < out_edges_.size());
        return out_edges_[idx];
    }

    size_t num_out_edges() const { return out_edges_.size(); }

    void add_out_edge(Edge *e);

    Edge *find_out_edge(Node *tail, Node *head);

    void feed_forward();

    void back_prop();

private:
    double act_;
    double output_;
    double act_der_;
    double error_;
    std::vector<Edge *> in_edges_;
    std::vector<Edge *> out_edges_;
    ActFunc *act_func_;
};

#endif
