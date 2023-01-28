
// 2294. Partition Array Such That Maximum Difference Is K
// https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/



class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {

        // idea: we can put horizontal slices with diff k accross nums

        sort(nums.begin(),nums.end());

        int ans = 1;

        int t = nums[0];
        for(int x: nums)
            if( x - t > k ) {
                t = x;
                ++ans;
            }

        return ans;
    }
};
