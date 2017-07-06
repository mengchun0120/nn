#ifndef __GROUP_LIST_HPP__
#define __GROUP_LIST_HPP__

#ifndef __COMMON_HPP__
#include "common.hpp"
#endif

#ifndef __GROUP_HPP__
#include "group.hpp"
#endif

template <typename T>
class GroupList {
public:
    typedef typename std::list<Group<T>>::iterator Iterator;
    typedef typename std::list<Group<T>>::const_iterator ConstIterator;

    GroupList():
        num_items_(0)
    {}

    virtual ~GroupList()
    {}

    size_t num_items() const
    {
        return num_items_;
    }

    Group<T>& add(size_t size)
    {
        groups_.emplace_back(size);
        num_items_ += size;
        return groups_.back();
    }

    Iterator begin()
    {
        return groups_.begin();
    }

    ConstIterator begin() const
    {
        return groups_.begin();
    }

    Iterator end()
    {
        return groups_.end();
    }

    ConstIterator end() const
    {
        return groups_.end();
    }

    void foreach(const std::function<void(T&)> &f)
    {
        for(auto it = begin(); it != end(); ++it) {
            for(auto it1 = it->begin(); it1 != it->end(); ++it1) {
                f(*it1);
            }
        }
    }

    void clear()
    {
        groups_.clear();
    }

protected:
    std::list<Group<T>> groups_;
    size_t num_items_;
};

#endif
