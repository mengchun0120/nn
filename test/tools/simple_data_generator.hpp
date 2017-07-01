#ifndef __SIMPLE_DATA_GENERATOR_HPP__
#define __SIMPLE_DATA_GENERATOR_HPP__

#include <cassert>
#include <random>
#include <functional>
#include <utility>

class SimpleDataGenerator {
    typedef std::pair<const char *, double (* const)(double)> NameFuncPair;

    static std::vector<NameFuncPair> name_func_pairs;
public:
    static SimpleDataGenerator *linear_generator(double slope, double intercept, double stddev);

    static SimpleDataGenerator *named_func_generator(const char *name, double stddev);

    SimpleDataGenerator(std::function<double(double)> f, double stddev):
        func_(f), rd_(), gen_()
    {
        assert(stddev > 0.0);
        dist_ = new std::normal_distribution<>(0.0, stddev);
        reset();
    }

    virtual ~SimpleDataGenerator()
    {
        delete dist_;
    }

    void reset()
    {
        gen_.seed(rd_());
    }

    double operator()(double x)
    {
        return func_(x) + (*dist_)(gen_);
    }

protected:
    std::function<double(double)> func_;
    std::random_device rd_;
    std::mt19937 gen_;
    std::normal_distribution<> *dist_;
};

#endif
