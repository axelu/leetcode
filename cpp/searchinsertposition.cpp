#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// Search Insert Position
// https://leetcode.com/problems/search-insert-position/

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        if ( nums.empty() ) return 0;
        if ( nums[0] >= target ) return 0;
        if ( nums.back() < target ) return nums.size();

        for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
            if ( *it == target || ( *(it -1) < target && *it > target ) ) return it - nums.begin();
        }
        return -1; // to satisfy compiler

    }
};

int main() {

    Solution s;

    vector<int> v;

    assert(s.searchInsert(v,5) == 0);

    v = {1,3,5,6};
    assert(s.searchInsert(v,5) == 2);

    v = {1,3,5,6};
    assert(s.searchInsert(v,2) == 1);

    v = {1,3,5,6};
    assert(s.searchInsert(v,7) == 4);

    v = {1,3,5,6};
    assert(s.searchInsert(v,0) == 0);

    v = {1,3,5,6};
    assert(s.searchInsert(v,6) == 3);

    v = {1,3,5,6};
    assert(s.searchInsert(v,1) == 0);




    return 0;
}
