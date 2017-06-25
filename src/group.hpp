#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
class Group {
public:
    typedef typename std::vector<T>::iterator Iterator;
    typedef typename std::vector<T>::const_iterator ConstIterator;
    typedef typename std::pair<Iterator, Iterator> Range;

    static size_t size(const Range &r)
    {
        return static_cast<size_t>(r.second - r.first);
    }

    Group(size_t size):
        items_(size)
    {
    }

    virtual ~Group()
    {
    }

    size_t size() const
    {
        return items_.size();
    }

    T& operator[](size_t idx)
    {
        assert(idx < size());
        return items_[idx];
    }

    const T& operator[](size_t idx) const
    {
        assert(idx < size());
        return items_[idx];
    }

    Iterator begin()
    {
        return items_.begin();
    }

    ConstIterator begin() const
    {
        return items_.begin();
    }

    Iterator end()
    {
        return items_.end();
    }

    ConstIterator end() const
    {
        return items_.end();
    }

    Range range(size_t start=0)
    {
        assert(start < size());
        return Range(begin()+start, end());
    }

    Range range(size_t start, size_t num)
    {
        assert(start + num < size());
        return Range(begin()+start, begin()+(start+num));
    }

private:
    std::vector<T> items_;
};

#endif
