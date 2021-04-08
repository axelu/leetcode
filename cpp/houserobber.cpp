#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

// House Robber
// https://leetcode.com/problems/house-robber/

class Solution {
public:
    int rob(vector<int>& nums) {
        if( nums.empty() ) return 0;
/*        if( nums.size() == 1 ) return nums[0];
        if( nums.size() == 2 )
            return ( nums[0] > nums[1] ) ? nums[0] : nums[1];
        if( nums.size() == 3 ) {
            int s = nums[0] + nums[2];
            return ( s > nums[1] ) ? s : nums[1];
        }
*/        
        return rob(nums.begin(), nums.end() - 1);
    }
private:
    int rob(vector<int>::iterator itb, vector<int>::iterator ite) {
        if( ite - itb == 0 )    // size 1
            return *itb;
        if( ite - itb == 1 )    // size 2
            return max(*itb, *ite);
        if( ite - itb == 2 )   // size 3
            return max(*itb + *ite, *(itb+1));
        if( ite - itb == 3 )   // size 4
            return max({*itb + *ite, *(itb+1) + *ite, *itb + *(itb+2)});
        
        int m = ( ite - itb ) / 2;
        auto itm = itb + m;

        // left
        int a = 0;
        int b = 0;
        if ( itm - itb >= 2 )
            a = rob(itb, itm - 2);
        if ( itm - itb >= 3 )
            b = rob(itb, itm - 3);

        // right
        int c = 0;
        int d = 0;
        if ( ite - itm >= 2 )
            c = rob(itm + 2, ite);
        if ( ite - itm >= 3 )
            d = rob(itm + 3, ite);

        int m1 = *itm + max(a,b) + max(c,d);
        
        // shift the middle by one
        itm = itm + 1;
        // left
        int e = b + *(itm-2);
        // int f = a;
        // right
        // int g = d;

        int m2 = *itm + max(a,e) + d;

        int m3 = b + *(itm-2) + c;

        return max({m1,m2,m3});
    }
};

int main() {
    Solution s;
    vector<int> v;

    // v = {2,7,9,3,1};
    // case 59/69 expected 7102
    v = {226,174,214,16,218,48,153,131,128,17,157,142,88,43,37,157,43,221,191,68,206,23,225,82,54,118,111,46,80,49,245,63,25,194,72,80,143,55,209,18,55,122,65,66,177,101,63,201,172,130,103,225,142,46,86,185,62,138,212,192,125,77,223,188,99,228,90,25,193,211,84,239,119,234,85,83,123,120,131,203,219,10,82,35,120,180,249,106,37,169,225,54,103,55,166,124};
    cout << "length " << v.size() << endl;
    cout << " result " << s.rob(v) << endl;


    return 0;
}
