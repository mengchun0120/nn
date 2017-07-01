#include <cmath>
#include <cstring>
#include <cstddef>
#include "simple_data_generator.hpp"

using namespace std;

vector<SimpleDataGenerator::NameFuncPair> SimpleDataGenerator::name_func_pairs{
    NameFuncPair("sin", sin),
    NameFuncPair("cos", cos),
    NameFuncPair("tan", tan),
    NameFuncPair("asin", asin),
    NameFuncPair("acos", acos),
    NameFuncPair("atan", atan),
    NameFuncPair("cosh", cosh),
    NameFuncPair("sinh", sinh),
    NameFuncPair("tanh", tanh),
    NameFuncPair("exp", exp),
    NameFuncPair("log", log),
    NameFuncPair("log10", log10),
    NameFuncPair("sqrt", sqrt)
};

SimpleDataGenerator *SimpleDataGenerator::linear_generator(double slope, double intercept, double stddev)
{
    auto linear_fn = [&](double x)->double { return slope * x + intercept; };
    SimpleDataGenerator *gen = new SimpleDataGenerator(linear_fn, stddev);
    return gen;
}

SimpleDataGenerator *SimpleDataGenerator::named_func_generator(const char *name, double stddev)
{
    double (*fptr)(double) = nullptr;

    for(auto it = name_func_pairs.begin(); it != name_func_pairs.end(); ++it) {
        if(strcmp(it->first, name) == 0) {
            fptr = it->second;
            break;
        }
    }

    if(!fptr) return nullptr;

    auto fn = [&](double x)->double { return (*fptr)(x); };
    SimpleDataGenerator *gen = new SimpleDataGenerator(fn, stddev);
    return gen;
}
