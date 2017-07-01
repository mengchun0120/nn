#ifndef __BATCH_HPP__
#define __BATCH_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

class Batch: public std::vector<double *> {
public:
    Batch(): std::vector<double *>() {}

    Batch(size_t size): std::vector<double *>(size) {}

    virtual ~Batch();
};

#endif
