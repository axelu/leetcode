
// 3176. Find the Maximum Length of a Good Subsequence I
// https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/





class Solution {
private:
    int mem[500][26];

    int rec(vector<int>& nums, int n, int pos, int k) {
        if( k == -1 )
            return 0;
        if( pos == n-1 )
            return 1;

        if( mem[pos][k] != -1 )
            return mem[pos][k];

        int ret = 1;

        for(int i = pos + 1; i < n; ++i) {
            int k_new = nums[pos] != nums[i] ? k-1 : k;

            ret = max(ret, 1 + rec(nums, n, i, k_new));
        }

        return mem[pos][k] = ret;
    }


public:
    int maximumLength(vector<int>& nums, int k) {
        // 1 <= nums.length <= 500
        // 0 <= k <= min(nums.length, 25)

        int n = nums.size();

        memset(mem,-1,sizeof mem);
        int ans = 1;
        for(int i = 0; i < n; ++i) {
            // each position can be a starting point of our subsequence
            int rem = n - i;
            if( ans >= rem )
                break;

            ans = max(ans, rec(nums, n, i, k));
        }

        return ans;
    }
};
