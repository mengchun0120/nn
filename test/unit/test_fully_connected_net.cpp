#include "act_func.hpp"
#include "fully_connected_net.hpp"
#include <unordered_set>

using namespace std;

bool all_unique_nodes(Group<Node>* nodes)
{
    unordered_set<Node *> found_nodes;

    for(auto node_it = nodes->begin(); node_it != nodes->end(); ++node_it) {
        Node *n = &(*node_it);
        if(found_nodes.find(n) != found_nodes.end()) {
            return false;
        }
        found_nodes.insert(n);
    }
    return true;
}

bool check_out_edges(Node *n, const Group<Node>::Range& heads)
{
    if(n->num_out_edges() != Group<Node>::size(heads)) {
        return false;
    }

    unordered_set<Node *> found_heads, matched_heads;

    for(auto head_it = heads.first; head_it != heads.second; ++head_it) {
        found_heads.insert(&(*head_it));
    }

    for(auto edge_it = n->out_edge_begin(); edge_it != n->out_edge_end(); ++edge_it) {
        if(found_heads.find((*edge_it)->head()) == found_heads.end() ||
           matched_heads.find((*edge_it)->head()) != matched_heads.end()) {
            return false;
        }
        matched_heads.insert((*edge_it)->head());
    }

    return true;
}

bool check_in_edges(Node *n, const Group<Node>::Range& tails)
{
    if(n->num_in_edges() != Group<Node>::size(tails)) {
        return false;
    }

    unordered_set<Node *> found_tails, matched_tails;

    for(auto tail_it = tails.first; tail_it != tails.second; ++tail_it) {
        found_tails.insert(&(*tail_it));
    }

    for(auto edge_it = n->in_edge_begin(); edge_it != n->in_edge_end(); ++edge_it) {
        if(found_tails.find((*edge_it)->tail()) == found_tails.end() ||
           matched_tails.find((*edge_it)->tail()) != matched_tails.end()) {
            return false;
        }
        matched_tails.insert((*edge_it)->tail());
    }

    return true;
}

int main(int argc, char *argv[])
{
    vector<size_t> layer_sizes{1, 2, 1};
    ActFunc act_func = ActFunc::relinear_act_func();
    FullyConnectedNet net(layer_sizes, &act_func, nullptr);

    assert(net.node_layer_count() == 3 && net.edge_layer_count() == 2
           && net.weight_layer_count() == 2);

    Group<Node> *nodes[] = {net.node_layer(0), net.node_layer(1), net.node_layer(2)};
    auto no_in_edge = [](Node& n) { return n.num_in_edges() == 0; };
    auto no_out_edge = [](Node& n) { return n.num_out_edges() == 0; };
    auto no_act_func = [](Node& n) { return n.get_act_func() == nullptr; };
    auto match_act_func = [&](Node& n) { return n.get_act_func() == &act_func; };

    for(size_t i = 0; i < 3; ++i) {
        assert(all_unique_nodes(net.node_layer(i)));

        if(i == 0) {
            assert(all_of(nodes[0]->begin(), nodes[0]->end(), no_in_edge));
        } else {
            auto connected_prev_layer = [&](Node& n) {
                return check_in_edges(&n, net.node_layer(i-1)->range());
            };
            assert(all_of(nodes[i]->begin(), nodes[i]->end()-1, connected_prev_layer));
        }

        if(i == 2) {
            assert(all_of(nodes[2]->begin(), nodes[2]->end(), no_out_edge));
        } else {
            auto connected_next_layer = [&](Node& n) {
                return check_out_edges(&n, net.node_layer(i+1)->range(0, layer_sizes[i+1]));
            };
            assert(all_of(nodes[i]->begin(), nodes[i]->end(), connected_next_layer));
        }

        if(i == 0 || i == 2) {
            assert(all_of(nodes[i]->begin(), nodes[i]->end(), no_act_func));
        } else {
            assert(all_of(nodes[i]->begin(), nodes[i]->end()-1, match_act_func));
        }
    }
}
