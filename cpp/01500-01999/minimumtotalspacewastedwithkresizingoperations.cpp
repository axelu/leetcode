
// 1959. Minimum Total Space Wasted With K Resizing Operations
// https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/



class Solution {
private:
    int mem[200][200];

    int rec(vector<int> &nums, int n, int i, int k) {
        if( i == n )
            return 0;
        if( k < 0 )
            return 200000001;

        if( mem[i][k] != -1 )
            return mem[i][k];

        // we have a choice
        // we can make an adjustment and move on
        // adjustments have to be the max of nums[i]

        int ret = 200000001;

        int mx = 0;     // max we have seen
        int sum = 0;    // running sum
        int waste;
        for(int j = i; j < n; ++j) {
            mx = max(mx,nums[j]);
            sum +=nums[j];
            // we would have to have the size adjusted to max seen
            // hence we can calculate the current waste[i,j] inclusive as
            waste = mx * (j-i+1) - sum;

            ret = min(ret, waste + rec(nums,n,j+1,k-1));
        }

        return mem[i][k] = ret;
    }

public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums,n,0,k);
    }
};
