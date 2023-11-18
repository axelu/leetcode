
// 2547. Minimum Cost to Split an Array
// https://leetcode.com/problems/minimum-cost-to-split-an-array/





class Solution {
private:
    int mem[1000];

    int rec(vector<int>& nums, int n, int pos, int k) {
        if( pos == n )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];

        int ret = INT_MAX;

        int l = 0;
        int cnt[1000];memset(cnt,0,sizeof cnt);
        for(int i = pos; i < n; ++i) {
            ++cnt[nums[i]];
            if( cnt[nums[i]] == 1 ) {
                // do nothing
            } else if( cnt[nums[i]] == 2 ) {
                l += 2;
            } else {
                l += 1;
            }

            ret = min(ret, k + l + rec(nums,n,i+1,k));
        }

        return mem[pos] = ret;
    }


public:
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        memset(mem,-1,sizeof mem);
        return rec(nums,n,0,k);
    }
};
