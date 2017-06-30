#include "batch.hpp"

Batch::~Batch()
{
    for(auto it = begin(); it != end(); ++it) {
        delete *it;
    }
}
