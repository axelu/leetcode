
// 136. Single Number
// https://leetcode.com/problems/single-number/


// 16 / 16 test cases passed, but took too long.
// Status: Time Limit Exceeded

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if ( nums.empty() ) return 0;
        if ( nums.size() == 1 ) return nums[0];
        // assume otherwise nums.size() is an odd number >= 3

        auto wi = nums.begin();
        for(auto ri = nums.begin()+1;ri!=nums.end();++ri) {
            if ( *wi == *ri) {
                if (ri - wi == 1) {
                    wi += 2;
                    ++ri;
                } else {
                    ++wi;
                    iter_swap(ri,wi);
                    ++wi;
                    ri = wi;
                }
            }
        }

        return *wi;
    }
};
