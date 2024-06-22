
// 3180. Maximum Total Reward Using Operations I
// https://leetcode.com/problems/maximum-total-reward-using-operations-i/




class Solution {
private:

    // worst case for sum would be picking 1999 + 2000
    // because 1 <= rewardValues[i] <= 2000
    // so max sum at most 3999
    int mem[2000][4000];

    int rec(vector<int>& nums, int n, int pos, int sum) {
        if( pos == n )
            return 0;

        if( mem[pos][sum] != -1 )
            return mem[pos][sum];

        // we have a choice
        //     pick the current pos if we can OR
        //     don't pick the current pos

        int a = 0;
        if( nums[pos] > sum )
            a = nums[pos] + rec(nums, n, pos+1, sum + nums[pos]);

        int b = rec(nums, n, pos+1, sum);

        return mem[pos][sum] = max(a,b);
    }


public:
    int maxTotalReward(vector<int>& rewardValues) {

        // we can eliminate dups and sort -> set
        set<int> st;
        for(int x: rewardValues)
            st.insert(x);
        vector<int> nums(st.begin(),st.end());
        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, 0);
    }
};
