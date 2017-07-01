#include "neural_net.hpp"
#include "init_weight.hpp"
#include "learn.hpp"

LearnEngine::LearnEngine(NeuralNet *net, EvaluateFunc *eval_func, WeightInitializer *weight_init)
{
    assert(net && eval_func && weight_init);
    net_ = net;
    eval_func_ = eval_func;
    weight_init_ = weight_init;
    dist_ = nullptr;
}

void LearnEngine::learn(const Batch& test_set, const Batch& test_target,
           const Batch& validate_set, const Batch& validate_target,
           size_t batch_size, size_t num_epochs, double learn_rate,
           size_t early_stop_thresh, std::function<void(double)> *epoch_func)
{
    assert(test_set.size() == test_target.size() &&
           validate_set.size() == validate_target.size());

    init_learn(test_set.size());

    static auto update_weight = [&](Weight& w) { w.set_value(w.value() - learn_rate * w.der()); };
    Batch batch_test(batch_size), batch_target(batch_size);
    double old_error, new_error;
    size_t stop_improve_steps = 0;

    for(size_t epoch = 0; epoch < num_epochs; ++epoch) {
        sample_one_batch(test_set, test_target, batch_test, batch_target);
        run_one_batch(batch_test, batch_target);

        net_->foreach_weight(update_weight);
        new_error = (*eval_func_)(net_, validate_set, validate_target);
        if(epoch > 0) {
            if(new_error < old_error) {
                stop_improve_steps = 0;
            } else {
                stop_improve_steps++;
                if(stop_improve_steps > early_stop_thresh) break;
            }
        }
        old_error = new_error;

        if(epoch_func) (*epoch_func)(new_error);
    }
}

void LearnEngine::init_learn(size_t num_tests)
{
    static auto init_weight = [this](Weight& w) { w.set_value((*weight_init_)()); };

    weight_init_->seed();
    net_->foreach_weight(init_weight);

    gen_.seed(rd_());
    if(dist_) delete dist_;
    dist_ = new std::uniform_int_distribution<unsigned int>(0, num_tests - 1);
}

void LearnEngine::sample_one_batch(const Batch& test_set, const Batch& test_target,
                      Batch& batch_test, Batch& batch_target)
{
    assert(batch_test.size() == batch_target.size() &&
           test_set.size() == test_target.size());

    for(size_t i = 0; i < batch_test.size(); ++i) {
        unsigned int idx = (*dist_)(gen_);
        batch_test[i] = test_set[idx];
        batch_target[i] = test_target[idx];
    }
}

void LearnEngine::run_one_batch(const Batch& batch_test, const Batch& batch_target)
{
    assert(batch_test.size() == batch_target.size());

    net_->zero_gradient();
    for(size_t i = 0; i < batch_test.size(); ++i) {
        net_->feed_forward(batch_test[i]);
        net_->back_prop(batch_target[i]);
        net_->add_gradient();
    }

    auto avg_gradient = [&](Weight& w){ w.set_der(w.der() / batch_test.size()); };

    net_->foreach_weight(avg_gradient);
}
