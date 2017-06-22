#include <cassert>
#include <vector>
#include "group_list.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    GroupList<int> glist;
    vector<int> arr{0, 1, 2, 3, 4};
    unsigned int i = 0;

    auto it_pair1 = glist.add(3);
    assert(it_pair1.second - it_pair1.first == 3 && glist.num_items() == 3);
    for(auto it = it_pair1.first; it != it_pair1.second; ++it, ++i) {
        *it = arr[i];
    }

    auto it_pair2 = glist.add(2);
    assert(it_pair2.second - it_pair2.first == 2 && glist.num_items() == 5);
    for(auto it = it_pair2.first; it != it_pair2.second; ++it, ++i) {
        *it = arr[i];
    }

    auto git = glist.begin();
    assert(!git.reach_end() && git.bound() == it_pair1);
    git.next();
    assert(!git.reach_end() && git.bound() == it_pair2);
    git.next();
    assert(git.reach_end());

    vector<int> arr1;
    auto get_items = [&](int& i){ arr1.push_back(i); };

    glist.foreach(get_items);
    assert(arr1.size() == arr.size());
    for(i = 0; i < arr.size(); ++i) {
        assert(arr1[i] == arr[i]);
    }
}
