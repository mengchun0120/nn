#ifndef __LEARN_HPP__
#define __LEARN_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

#ifndef __EVAL_HPP__
#include "eval.hpp"
#endif

class NeuralNet;
class WeightInitializer;

class LearnEngine {
public:
    LearnEngine(NeuralNet *net, EvaluateFunc *eval_func, WeightInitializer *weight_init);

    virtual ~LearnEngine()
    {
        delete dist_;
    }

    void learn(const Batch& test_set, const Batch& test_target,
               const Batch& validate_set, const Batch& validate_target,
               size_t batch_size, size_t num_epochs, double learn_rate, size_t early_stop_thresh,
               std::function<void(double)> *epoch_func=nullptr);

private:
    NeuralNet *net_;
    EvaluateFunc *eval_func_;
    WeightInitializer *weight_init_;
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<unsigned int> *dist_;

    void init_learn(size_t num_tests);

    void sample_one_batch(const Batch& test_set, const Batch& test_target,
                          Batch& batch_test, Batch& batch_target);

    void run_one_batch(const Batch& batch_test, const Batch& batch_targets);
};

#endif
