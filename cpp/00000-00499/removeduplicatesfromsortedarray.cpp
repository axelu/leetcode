#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// 26. Remove Duplicates from Sorted Array
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        if ( nums.empty() ) return 0;
        if ( nums.size() == 1 ) return 1;

        auto wit = nums.begin() + 1;
        for(auto rit = nums.begin() + 1; rit != nums.end(); ++rit) {
            if( *(rit-1) != *rit ) {
                if( wit != rit ) *wit = *rit;
                ++wit;
            }
        }

        return wit - nums.begin();
    }
};

int main() {

    Solution s;

    vector<int> v;

    cout << "in = " << "{}" << endl;
    assert(s.removeDuplicates(v) == 0);

    cout << "in = " << "{1}" << endl;
    v = {1};
    assert(s.removeDuplicates(v) == 1);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{1,1,2}" << endl;
    v = {1,1,2};
    assert(s.removeDuplicates(v) == 2);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{0,0,1,1,1,2,2,3,3,4}" << endl;
    v = {0,0,1,1,1,2,2,3,3,4};
    assert(s.removeDuplicates(v) == 5);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{0,0,0,0,0,0,0,0,0,0,0}" << endl;
    v = {0,0,0,0,0,0,0,0,0,0,0};
    assert(s.removeDuplicates(v) == 1);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{0,0,0,0,0,0,0,0,0,0,1}" << endl;
    v = {0,0,0,0,0,0,0,0,0,0,1};
     assert(s.removeDuplicates(v) == 2);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{0,1,2,3,4,5,6,7,8,9,10}" << endl;
    v = {0,1,2,3,4,5,6,7,8,9,10};
     assert(s.removeDuplicates(v) == 11);
    for(auto i : v) cout << i;
    cout << endl;






    return 0;
}
