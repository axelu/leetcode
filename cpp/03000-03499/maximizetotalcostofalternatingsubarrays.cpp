
// 3196. Maximize Total Cost of Alternating Subarrays
// https://leetcode.com/problems/maximize-total-cost-of-alternating-subarrays/



class Solution {
private:

    long long mem[100000];

    long long rec(vector<int>& nums, const int n, const int pos) {
        if( pos == n )
            return 0LL;

        if( mem[pos] != -1LL )
            return mem[pos];

        long long ret = nums[pos] + rec(nums, n, pos+1);
        long long t = nums[pos];

        for(int i = 1; i < 3 && pos + i < n; ++i) {

            if( i % 2 )
                t -= nums[pos+i];
            else
                t += nums[pos+i];

            ret = max(ret, t + rec(nums, n, pos + i + 1));
        }

        return mem[pos] = ret;
    }


public:
    long long maximumTotalCost(vector<int>& nums) {
        int nums_sz = nums.size();

        // ignore consecutive 0s
        vector<int> v{nums[0]};
        for(int i = 1; i < nums_sz; ++i)
            if( nums[i] != 0 || (nums[i] == 0 && nums[i-1] != 0) )
                v.push_back(nums[i]);

        // TODO ignore consecutive opposites, because the best we can get is 0


        int n = v.size();
        memset(mem,-1,sizeof mem);
        return rec(v, n, 0);
    }
};
