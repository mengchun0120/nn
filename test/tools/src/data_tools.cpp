#include <cassert>
#include <fstream>
#include <stdexcept>
#include <random>
#include <utility>
#include "data_tools.hpp"

using namespace std;

void shuffle(Batch& inputs, Batch& targets)
{
    assert(inputs.size() == targets.size());

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist;
    size_t size = inputs.size();

    for(size_t i = 0; i < inputs.size() - 1; ++i, --size) {
        size_t r = i + static_cast<size_t>(size * dist(gen));
        if(i != r) {
            swap(inputs[i], inputs[r]);
            swap(targets[i], targets[i]);
        }
    }
}

void read_data(const char *data_file, size_t data_count, size_t input_size, size_t target_size,
               double train_ratio, Batch &train_inputs, Batch &train_targets,
               double validate_ratio, Batch &validate_inputs, Batch &validate_targets,
               Batch &test_inputs, Batch &test_targets)
{
    if(!data_file || data_count == 0 || input_size == 0 || target_size == 0 ||
       train_ratio <= 0.0 || validate_ratio <= 0 || train_ratio + validate_ratio >= 1.0) {

        throw runtime_error("Invalid parameters");
    }

    size_t train_count = data_count * train_ratio;
    size_t validate_count = data_count * validate_ratio;
    size_t test_count = data_count - train_count - validate_count;

    if(train_count == 0 || validate_count == 0 || test_count == 0) {
        throw runtime_error("Invalid parameters");
    }

    train_inputs.resize(train_count);
    train_targets.resize(train_count);
    validate_inputs.resize(validate_count);
    validate_targets.resize(validate_count);
    test_inputs.resize(test_count);
    test_targets.resize(test_count);

    Batch all_inputs(data_count);
    Batch all_targets(data_count);
    ifstream in(data_file);
    size_t read_count, i;

    for(read_count = 0; read_count < data_count && in.good(); ++read_count) {
        double *input = new double[input_size];
        for(i = 0; i < input_size && in.good(); ++i) {
            in >> input[i];
        }

        if(i < input_size) break;

        double *target = new double[target_size];
        for(i = 0; i < target_size && in.good(); ++i) {
            in >> target[i];
        }

        if(i < target_size) break;

        all_inputs.push_back(input);
        all_targets.push_back(target);
    }

    if(read_count < data_count) {
        throw runtime_error("Error happened when reading data");
    }

    shuffle(all_inputs, all_targets);

    size_t j = 0;

    for(i = 0; i < train_count; ++i, ++j) {
        train_inputs[i] = all_inputs[j];
        train_targets[i] = all_targets[j];
    }

    for(i = 0; i < validate_count; ++i, ++j) {
        validate_inputs[i] = all_inputs[j];
        validate_targets[i] = all_targets[j];
    }

    for(i = 0; i < test_count; ++i, ++j) {
        test_inputs[i] = all_inputs[j];
        test_targets[i] = all_targets[j];
    }
}
