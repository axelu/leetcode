
// 2597. The Number of Beautiful Subsets
// https://leetcode.com/problems/the-number-of-beautiful-subsets/





class Solution {
private:
    int rec(vector<int>& nums, int n, int i, int k, int cnt[], int counter) {
        if( i == n )
            return counter != 0;

        // we have a choice

        // don't include int at current index
        int ret = rec(nums,n,i+1,k,cnt,counter);

        // include char at current index, if we can
        if( nums[i] - k <= 0 || cnt[nums[i]-k] == 0 ) {
            ++counter;
            ++cnt[nums[i]];
            ret += rec(nums,n,i+1,k,cnt,counter);
            // backtrack
            --cnt[nums[i]];
            --counter;
        }


        return ret;
    }

public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int n = nums.size();

        // because we are not being asked to return the actual
        // subsets, but only the number of 'beautiful' subsets,
        // we can reorder nums
        sort(nums.begin(),nums.end());

        int cnt[1001]; // 1 <= nums[i] <= 1000
        memset(cnt,0,sizeof cnt);

        return rec(nums,n,0,k,cnt,0);
    }
};
