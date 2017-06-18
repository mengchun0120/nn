#ifndef __EDGE_HPP__
#define __EDGE_HPP__

class Node;
class Weight;

class Edge {
public:
    Edge(Node *tail=nullptr, Node *head=nullptr, Weight *weight=nullptr);

    virtual ~Edge() {}

    Node *tail() { return tail_; }

    const Node *tail() const { return tail_; }

    void set_tail(Node *t) { tail_ = t; }

    Node *head() { return head_; }

    const Node *head() const { return head_; }

    void set_head(Node *h) { head_ = h; }

    Weight *weight() { return weight_; }

    const Weight *weight() const { return weight_; }

    void set_weight(Weight *w) { weight_ = w; }

protected:
    Node *tail_, *head_;
    Weight *weight_;
};

#endif
