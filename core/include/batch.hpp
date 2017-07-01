#ifndef __BATCH_HPP__
#define __BATCH_HPP__

#include <cstddef>
#include <vector>

class Batch: public std::vector<double *> {
public:
    Batch(): std::vector<double *>() {}

    Batch(size_t size): std::vector<double *>(size) {}

    virtual ~Batch();
};

#endif
