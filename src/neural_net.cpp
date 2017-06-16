#include "neural_net.hpp"

NeuralNet::NeuralNet(unsigned int num_inputs, unsigned int num_hiddens, unsigned int num_outputs, unsigned int num_weights):
    num_inputs_(num_inputs),
    num_hiddens_(num_hiddens),
    num_outputs_(num_outputs),
    nodes_(num_inputs + num_outputs + num_hiddens + 1),
    weights_(num_weights)
{
}

void NeuralNet::bind_weight(Index weight_id, Index tail_id, Index head_id)
{
    assert(tail_id < nodes_.size() && head_id < nodes_.size() && weight_id < weights_.size());

    nodes_[tail_id].add_out_weight(weight_id);
    nodes_[head_id].add_in_weight(weight_id);
    weights_[weight_id].add_tail(tail_id);
    weights_[weight_id].add_head(head_id);
}
