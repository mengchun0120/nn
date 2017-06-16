#ifndef __OUTPUT_FUNC_HPP__
#define __OUTPUT_FUNC_HPP__

#ifndef __NODE_HPP__
#include "node.hpp"
#endif

typedef void (*output_func)(std::vector<Node>::iterator output_begin, std::vector<Node>::iterator output_end);

void identity_output(std::vector<Node>::iterator output_begin, std::vector<Node>::iterator output_end);

#endif
