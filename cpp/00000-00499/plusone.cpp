#include <iostream>
#include <cassert>
#include <vector>

// 66. Plus One
// https://leetcode.com/problems/plus-one/

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> r;

        if ( digits.empty() ) return {1};

        auto it = digits.rbegin();
        int carried = 1;

        while ( it != digits.rend() || carried != 0 ) {
            carried += ( it !=digits.rend() ) ? *it : 0;
            r.insert(r.begin(), carried % 10);
            carried /= 10;
    
            if ( it != digits.rend() ) ++it;
            
        }

        return r;
    }
};


int main() {

    Solution s;

    vector<int> v1in = {1,2,3};
    vector<int> v1out = {1,2,4};
    assert(s.plusOne(v1in) == v1out);


    vector<int> v2in = {9,9,9};
    vector<int> v2out = {1,0,0,0};
    assert(s.plusOne(v2in) == v2out);

    vector<int> v3in = {};
    vector<int> v3out = {1};
    assert(s.plusOne(v3in) == v3out);

    return 0;
}
