#ifndef __GROUP_LIST_HPP__
#define __GROUP_LIST_HPP__

#include <cstddef>
#include <vector>
#include <list>
#include <utility>
#include <functional>

template <typename T>
class GroupList {
    friend class GroupIterator;

public:
    typedef typename std::vector<T> Group;
    typedef typename std::list<Group> Groups;
    typedef typename Group::iterator ItemIterator;
    typedef typename std::pair<ItemIterator, ItemIterator> ItemIterPair;

    class GroupIterator {
        friend class GroupList;
    public:
        bool reach_end()
        {
            return iter_ == end_;
        }

        void next()
        {
            assert(iter_ != end_);
            ++iter_;
        }

        ItemIterPair bound()
        {
            return ItemIterPair(iter_->begin(), iter_->end());
        }

    private:
        GroupIterator(GroupList& gl):
            iter_(gl.groups_.begin()), end_(gl.groups_.end())
        {}

        typename Groups::iterator iter_;
        typename Groups::iterator end_;
    };

    GroupList():
        num_items_(0)
    {}

    virtual ~GroupList()
    {}

    ItemIterPair add(size_t num_items)
    {
        groups_.emplace_back(num_items);
        num_items_ += num_items;
        return ItemIterPair(groups_.back().begin(), groups_.back().end());
    }

    size_t num_items() const
    {
        return num_items_;
    }

    GroupIterator begin()
    {
        return GroupIterator(*this);
    }

    void foreach(std::function<void(T&)> f)
    {
        for(GroupIterator it(*this); !it.reach_end(); it.next()) {
            ItemIterPair iter_pair = it.bound();
            for(auto i = iter_pair.first; i != iter_pair.second; ++i) {
                f(*i);
            }
        }
    }

//protected:
    Groups groups_;
    size_t num_items_;
};

#endif
