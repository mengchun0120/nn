#include "output_func.hpp"

void identity_output(std::vector<Node>::iterator output_begin, std::vector<Node>::iterator output_end)
{
    for(auto it = output_begin; it != output_end; ++it) {
        it->set_output(it->get_act());
    }
}
