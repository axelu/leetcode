
// 813. Largest Sum of Averages
// https://leetcode.com/problems/largest-sum-of-averages/




/*
class Solution {
private:
    double mem[100][100][101];
    double avg[100][100];

    double rec(vector<int>& nums, int s, int e, int k) {
        // k number of remaining partitions
        // 1 <= k <= e - s + 1

        if( mem[s][e][k] != -1.0 )
            return mem[s][e][k];

        double ret = avg[s][e];
        double l,r;
        for(int i = s; i < e; ++i) {
            for(int j = 1; j < k; ++j) {
                l = rec(nums,s,i,j);
                r = rec(nums,i+1,e,k-j);

                ret = max(ret,l+r);
            }
        }

        return mem[s][e][k] = ret;
    }


public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + nums[i];

        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                avg[i][j] = (double)(prefixSum[j+1] - prefixSum[i]) / (j - i + 1);

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                for(int o = 0; o <= k; ++o)
                    mem[i][j][o] = -1.0;

        return rec(nums,0,n-1,k);
    }
};
*/

class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + nums[i];

        if( k == 1 )
            return (double)prefixSum[n] / n;

        double dp[n][n][k+1];
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                dp[i][j][1] = (double)(prefixSum[j+1] - prefixSum[i]) / (j - i + 1);


        for(int length = 2; length <= n; ++length) { // length

            for(int l = 0, r = length - 1; r < n; ++l, ++r) {

                for(int w = 2; w <= min(length,k); ++w) {
                    dp[l][r][w] = -1.0;
                    for(int i = l; i < r; ++i) {
                        int left_k  = min(i-l+1,w-1);
                        int right_k = w - left_k;
                        dp[l][r][w] = max(dp[l][r][w], dp[l][i][left_k] + dp[i+1][r][right_k]);
                    }
                }
            }
        }

        return dp[0][n-1][k];
    }
};
