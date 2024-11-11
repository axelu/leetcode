
// 3250. Find the Count of Monotonic Pairs I
// https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/




class Solution {
private:
    const long mod = 1000000007;

    long mem[2000][51];

    long rec(vector<int>& nums, int n, int i, int pre1) {
        int pre2 = nums[i-1] - pre1;
        // cout << "rec pos " << i << " pre1 " << pre1 << " pre2 " << pre2 << endl;

        if( i == n )
            return 1L;

        if( mem[i][pre1] != -1L )
            return mem[i][pre1];

        long ret = 0L;

        // we are asked to create two arrays
        //    arr1 monotonically non-decreasing
        //    arr2 monotonically non-increasing,
        // the value in arr1 at i can be pre1 <= val1 <= nums[i]
        // the value in arr2 will be val2 = nums[i] - val1 and must be pre2 >= val2 >= 0

        int val1 = pre1;
        int val2 = nums[i] - val1;

        // TODO we can more smartly picking the begin of our loop so that in the initial iteration both conditions are met

        for(; val1 <= nums[i] && val2 >= 0; ++val1, --val2) {
            // we are only here if the condition for arr1 is met
            // so we need to check condition for arr2
            if( val2 <= pre2 )
                ret = (ret + rec(nums, n, i+1, val1)) % mod;
        }

        return mem[i][pre1] = ret;
    }





public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 2000; 1 <= nums[i] <= 50
        if( n == 1 )
            return nums[0] + 1;

        // TODO we could look ahead to get max and min
        // to help only checking applicable range

        long ans = 0L;


        memset(mem,-1,sizeof mem);
        for(int i = 0; i <= nums[0]; ++i)
            ans = (ans + rec(nums, n, 1, i)) % mod;

        return ans;
    }
};
