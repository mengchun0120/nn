#include <cassert>
#include <vector>
#include "group_list.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    GroupList<int> glist;
    vector<int> arr{0, 1, 2, 3, 4};
    unsigned int i;

    Group<int>& g1 = glist.add(3);
    auto it1 = g1.begin();
    for(i = 0; i < 3; ++i, ++it1) {
        *it1 = arr[i];
    }
    assert(g1.size() == 3 && glist.num_items() == 3);

    Group<int>& g2 = glist.add(2);
    auto it2 = g2.begin();
    for(; i < 5; ++i, ++it2) {
        *it2 = arr[i];
    }
    assert(g2.size() == 2 && glist.num_items() == 5);

    vector<int> arr1;
    auto get_items = [&](int& i){ arr1.push_back(i); };

    glist.foreach(get_items);
    assert(arr1.size() == arr.size());
    for(i = 0; i < arr.size(); ++i) {
        assert(arr1[i] == arr[i]);
    }
}
