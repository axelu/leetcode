
// 698. Partition to K Equal Sum Subsets
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
// day 30 Sep 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/640/week-5-september-29th-september-30th/3993/




class Solution {
private:
    bool rec(int nums[], int n, int pos, int sum, int k, int target, int& used) {
        if( k == 1 )
            return true;

        if( sum == target )
            return rec(nums,n,0,0,k-1,target,used);

        for(int i = pos; i < n; ++i) {
            if( !((used >> i) & 1) && sum + nums[i] <= target ) {
                used |= 1 << i;     // set bit
                if( rec(nums,n,i+1,sum+nums[i],k,target,used) )
                    return true;
                used &= ~(1 << i);  // clear bit
            }
        }

        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // prerequisite: the sum of [nums[0],nums[n-1]] needs to be divisible by k
        // no element in nums can be bigger than the target sum, because
        // 1 <= nums[i] <= 10^4

        if( k == 1 )
            return true;

        int n = nums.size(); // 1 <= k <= nums.length <= 16

        int total = 0;
        for(int i = 0; i < n; ++i)
            total += nums[i];

        if( total % k != 0 )
            return false;

        int target = total / k; // what each subset must sum to

        int used = 0;
        return rec(nums.data(),n,0,0,k,target,used);
    }
};
