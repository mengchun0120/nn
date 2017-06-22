#ifndef __INIT_WEIGHT_HPP__
#define __INIT_WEIGHT_HPP__

#include <functional>
#include <random>

typedef std::functional<void()> WeightInitializer;

class UniformRandomWeightInitializer {
public:
    UniformRandomWeightInitializer(double min, double max):
        gen_(std::random_device()),
        dis_(min, max)
    {}

    void operator()()
    {
        return dis_(gen_);
    }

private:
    std::mt19937 gen_;
    std::uniform_real_distribution<> dis_;
};

class NormalRandomWeightInitializer {
public:
    NormalRandomWeightInitializer(double mean, double stddev):
        gen_(std::random_device()),
        dis_(mean, stddev)
    {}

    void operator()()
    {
        return dis_(gen_);
    }

private:
    std::mt19937 gen_;
    std::normal_distribution<> dis_;
};

#endif
