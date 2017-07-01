#ifndef __INIT_WEIGHT_HPP__
#define __INIT_WEIGHT_HPP__

#include <functional>
#include <random>

class WeightInitializer {
public:
    WeightInitializer():
        rd_(),
        gen_(rd_())
    {}

    void seed()
    {
        gen_.seed(rd_());
    }

    virtual double operator()() = 0;

protected:
    std::random_device rd_;
    std::mt19937 gen_;
};

class UniformRandomWeightInitializer: public WeightInitializer {
public:
    UniformRandomWeightInitializer(double min, double max):
        dis_(min, max)
    {}

    double operator()()
    {
        return dis_(gen_);
    }

private:
    std::uniform_real_distribution<> dis_;
};

class NormalRandomWeightInitializer: public WeightInitializer {
public:
    NormalRandomWeightInitializer(double mean, double stddev):
        dis_(mean, stddev)
    {}

    double operator()()
    {
        return dis_(gen_);
    }

private:
    std::normal_distribution<> dis_;
};

#endif
