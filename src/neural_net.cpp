#include "neural_net.hpp"

NeuralNet::NeuralNet():
    input_start_(0),
    input_size_(0),
    output_start_(0),
    output_size_(0)
{

}

size_t NeuralNet::add_node(ActFunc *act_func)
{
    nodes_.emplace_back(act_func);
    return nodes_.size() - 1;
}

void NeuralNet::set_input(size_t input_start, size_t input_size)
{
    assert(input_start < nodes_.size() && input_start + input_size <= nodes_.size());
    input_start_ = input_start;
    input_size_ = input_size;
}

void NeuralNet::set_output(size_t output_start, size_t output_size)
{
    assert(output_start < nodes_.size() && output_start + output_size <= nodes_.size());
    output_start_ = output_start;
    output_size_ = output_size;
}

size_t NeuralNet::add_weight()
{
    weights_.emplace_back();
    return weights_.size() - 1;
}

size_t NeuralNet::add_edge(size_t tail_idx, size_t head_idx, size_t weight_idx)
{
    edges_.emplace_back(node(tail_idx), node(head_idx), weight(weight_idx));
    return edges_.size() - 1;
}
