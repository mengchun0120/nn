#ifndef __DATA_TOOLS_HPP__
#define __DATA_TOOLS_HPP__

#include <cstddef>
#include <vector>
#include "batch.hpp"

void shuffle(Batch& inputs, Batch& targets);

void read_data(const char *data_file, size_t input_size, size_t target_size,
               double train_data_ratio, Batch &train_inputs, Batch &train_targets,
               double validate_data_ratio, Batch &validate_inputs, Batch &validate_targets,
               Batch &test_inputs, Batch &test_targets);

#endif
