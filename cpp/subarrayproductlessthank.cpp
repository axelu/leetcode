
// day 28 September 2020 challenge
// Subarray Product Less Than K
// https://leetcode.com/problems/subarray-product-less-than-k/



#include <iostream>
#include <cassert>

#include <vector>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // 0 < nums[i] < 1000
        // because product of subarray has to be LESS than k
        // and nums[i] cannot be 0, we can rule out k <= 1
        if( k <= 1 ) return 0;

        // 0 < nums.length <= 50000
        // 0 < nums[i] < 1000
        // max possible product 50000 * 999 = 49950000
        // int is large enough to hold product
        int p = 1; // init

        int r = 0;
        auto itl = nums.begin();
        auto itr = itl;
        for(; itr != nums.end(); ++itr) {
            p *= *itr;
            // cout << "curr p " << p << endl;
            // cout << "idx l  " << distance(nums.begin(), itl) << endl;
            // cout << "idx r  " << distance(nums.begin(), itr) << endl;
            // advance left iterator if p >= k
            // its ok if iterators cross!!!
            while( p >= k ) p /= *(itl++);
            // cout << "new p " << p << endl;
            // cout << "idx l  " << distance(nums.begin(), itl) << endl;
            // cout << "idx r  " << distance(nums.begin(), itr) << endl;
            r += itr - itl + 1;
        }

        return r;
    }
};
/*
int main() {
    Solution s;
    vector<int> nums;
    int k;
    int r;

    nums = {10, 5, 2, 6};
    k = 100;
    r = s.numSubarrayProductLessThanK(nums,k);
    cout << "result " << r << endl;
    assert(r == 8);

    nums = {1,1,5,5,1,1,1};
    k = 4;
    r = s.numSubarrayProductLessThanK(nums,k);
    cout << "result " << r << endl;
    assert(r == 9);





    return 0;
}*/
