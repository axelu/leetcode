
// 2750. Ways to Split Array Into Good Subarrays
// https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/



class Solution {
public:
    int numberOfGoodSubarraySplits(vector<int>& nums) {
        int n = nums.size();

        long mod = 1000000007;
        long ans = 1;
        int last = -1;
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 ) {
                if( last != -1 )
                    ans = (ans * (i - last )) % mod;
                last = i;
            }
        }

        return last == -1 ? 0 : ans;
    }
};
