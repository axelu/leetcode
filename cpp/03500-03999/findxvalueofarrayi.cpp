
// 3524. Find X Value of Array I
// https://leetcode.com/problems/find-x-value-of-array-i/




/* transition matrix current remainder x prior remainder for a given k
   k = 2
     0 1
   0 0 0
   1 0 1

   k = 3
     0 1 2
   0 0 0 0
   1 0 1 2
   2 0 2 1

   k = 4
     0 1 2 3
   0 0 0 0 0
   1 0 1 2 3
   2 0 2 0 2
   3 0 3 2 1

   k 0 5
     0 1 2 3 4
   0 0 0 0 0 0
   1 0 1 2 3 4
   2 0 2 4 1 3
   3 0 3 1 4 2
   4 0 4 3 2 1
 */
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        // constraints
        // 1 <= nums[i] <= 1e9
        // 1 <= nums.length <= 1e5
        // 1 <= k <= 5

        long long n = nums.size();

        vector<long long> ans(k, 0LL);

        if( n == 1 ) {
            int rem = nums[0] % k;
            ans[rem] = 1;
            return ans;
        }

        if( k == 1 ) {
            ans[0] = n * ((n+1)/2.0);
            return ans;
        }

        // let dp[i][rem] be the number of subarrays ending at i
        // with a product whos remainder k is rem

        // vector<vector<long long>> dp(n, vector<long long>(k, 0LL));
        long long dp[n][5];memset(dp,0,sizeof dp);

        // i = 0;
        dp[0][nums[0]%k] = 1LL;

        for(int i = 1; i < n; ++i) {
            int cur_rem = nums[i] % k;
            for(int rem = 0; rem < k; ++rem) {
                if( dp[i-1][rem] == 0 )
                    continue;
                int new_rem = (rem * cur_rem) % k;
                dp[i][new_rem] += dp[i-1][rem];
            }
            // add ourselves
            dp[i][cur_rem] += 1LL;
        }

        for(int i = 0; i < n; ++i)
            for(int rem = 0; rem < k; ++rem)
                ans[rem] += dp[i][rem];

        return ans;
    }
};
