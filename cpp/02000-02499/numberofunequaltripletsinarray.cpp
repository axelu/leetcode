
// 2475. Number of Unequal Triplets in Array
// https://leetcode.com/problems/number-of-unequal-triplets-in-array/




class Solution {
public:
    int unequalTriplets(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;

        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {
                if( nums[i] == nums[j] )
                    continue;
                for(int k = j+1; k < n; ++k) {
                    if( nums[i] == nums[k] || nums[j] == nums[k])
                        continue;
                    ++cnt;
                }
            }
        }

        return cnt;
    }
};
