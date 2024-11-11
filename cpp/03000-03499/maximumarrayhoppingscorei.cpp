
// 3205. Maximum Array Hopping Score I
// https://leetcode.com/problems/maximum-array-hopping-score-i/




class Solution {
private:
    int rec(vector<int>& nums, int n, int i, int mem[]) {
        if( i == n-1 )
            return 0;

        if( mem[i] != -1 )
            return mem[i];

        int ret = INT_MIN;

        // we will figure out the gain of the hop
        for(int j = i+1; j < n; ++j) {

            int score = (j-i) * nums[j];
            ret = max(ret, score + rec(nums, n, j, mem));
        }

        return mem[i] = ret;
    }




public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        int mem[n];memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, mem);
    }
};
