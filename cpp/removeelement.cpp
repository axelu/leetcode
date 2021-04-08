#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// Remove Element
// https://leetcode.com/problems/remove-element/

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        if ( nums.empty() ) return 0;
        if ( nums.size() == 1 ) {
            if ( nums[0] == val ) {
                return 0;
            } else {
                return 1;
            }
        }

        auto wit = nums.begin();
        for(auto rit = nums.begin(); rit != nums.end(); ++rit) {
            if ( *rit == val && *wit != val ) {
                wit = rit;
            } else if ( *rit != val && *wit == val ) {
                *wit = *rit;
                *rit = val;
                while ( *wit != val && wit < rit ) wit++;
            }
        }

        return ( wit == nums.begin() && *wit != val ) ? nums.size() : wit - nums.begin();
    }
};

int main() {

    Solution s;

    vector<int> v;

    cout << "in = " << "{},5" << endl;
    assert(s.removeElement(v,5) == 0);

    cout << "in = " << "{1},1" << endl;
    v = {1};
    assert(s.removeElement(v,1) == 0);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{1},0" << endl;
    v = {1};
    assert(s.removeElement(v,0) == 1);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,2,2,3},3" << endl;
    v = {3,2,2,3};
    assert(s.removeElement(v,3) == 2);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{0,1,2,2,3,0,4,2},2" << endl;
    v = {0,1,2,2,3,0,4,2};
    assert(s.removeElement(v,2) == 5);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,3},3" << endl;
    v = {3,3};
    assert(s.removeElement(v,3) == 0);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,3,3},3" << endl;
    v = {3,3,3};
    assert(s.removeElement(v,3) == 0);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,3,3,4},3" << endl;
    v = {3,3,3,4};
    assert(s.removeElement(v,3) == 1);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,4},3" << endl;
    v = {3,4};
    assert(s.removeElement(v,3) == 1);
    for(auto i : v) cout << i;
    cout << endl;

    cout << "in = " << "{3,3},5" << endl;
    v = {3,3};
    assert(s.removeElement(v,5) == 2);
    for(auto i : v) cout << i;
    cout << endl;


    return 0;
}
