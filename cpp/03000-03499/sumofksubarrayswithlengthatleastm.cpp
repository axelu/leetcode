
// 3473. Sum of K Subarrays With Length at Least M
// https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/

class Solution {
private:
    const int INF = 20000001;

public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();

        vector<int> prefixSum(n+1);
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        // from the hint: 
        // Let dp[i][j] be max sum with i subarrays for the first j elements
        vector<vector<int>> dp(k+1, vector<int>(n+1, -INF));
        // if we have not selected any subarrays, then the sum is 0
        for(int j = 0; j <= n; ++j)
            dp[0][j] = 0;

        for(int i = 1; i <= k; ++i) {
            int local_max = -INF;

            // there are i-1 subarrays selected before us
            // so we must select at minimum i * m elements
            // there will be k-i subarrays be selected after us,
            // but we need to carry the max ans forward, hence going up to n
            for(int j = m * i; j <= n; ++j) {
                local_max = max(local_max, dp[i-1][j-m]);

                dp[i][j] = prefixSum[j] - prefixSum[j-m] + local_max;
                if( j > m*i )
                    dp[i][j] = max(dp[i][j], dp[i][j-1] + nums[j-1]);
            } 
        }

        // min selected if k subarrays
        int j_min = m * k;
        int ans = -INF;
        for(int j = j_min; j <= n; ++j)
            ans = max(ans, dp[k][j]);

        return ans;
    }
};

// passes 617 / 624 test cases, then TLE as of 3/3/2025


class Solution {
private:
    const int INF = 20000001;

    int mem[2000][2001];

    int rec(vector<int>& nums, int k, int m, int i) {
        // cout << "rec i " << i << " k " << k << endl;
        int n = nums.size();
        if( k == 0 )
            return 0;
        if( i == n )
            return 0;
        if( n - i < m )
            return -INF;

        if( mem[i][k] != -1 )
            return mem[i][k];

        // when we arrive at i, it is guaranteed that
        // we can make k non-overlpping subarrays of at least length m

        // we have a choice
        //     starting at i, construct len m subarray up to max len and rec OR
        //     start at the next i if we can

        int ret = -INF;

        // up do what index j can we expand a subarray starting at i?
        // there will be k-1 subarrays of length m at minimal behind us
        int j_max = n - ((k-1) * m) - 1;
        int mx = -INF;
        int sum = 0;
        for(int j = i; j <= j_max; ++j) {
            sum += nums[j];
            if( j - i + 1 >= m ) {
                mx = max(mx, sum);
                ret = max(ret, mx + rec(nums, k-1, m, j+1));
            }
        }

        int i_max = n - (k * m);
        if( i < i_max )
            ret = max(ret, rec(nums, k, m, i+1));

        return mem[i][k] = ret;
    }

public:
    int maxSum(vector<int>& nums, int k, int m) {

        memset(mem,-1,sizeof mem);
        return rec(nums, k, m, 0);
    }
};
