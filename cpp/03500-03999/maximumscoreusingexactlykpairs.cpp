
// 3836. Maximum Score Using Exactly K Pairs
// https://leetcode.com/problems/maximum-score-using-exactly-k-pairs/




class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(); // 1 <= n <= 100
        int m = nums2.size(); // 1 <= m <= 100
        // 1 <= k <= min(n, m)

        // TODO use 2 vectors vector<vector<long long>>(n+1, vector<long long>(m+1,LLONG_MIN)) and swap them
        vector<vector<vector<long long>>> dp(k+1, vector<vector<long long >>(n+1, vector<long long>(m+1, LLONG_MIN)));
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j)
                dp[0][i][j] = 0;

        for(int pair = 1; pair <= k; ++pair) {
            // cout << "pair " << pair << endl;
            int i_min = k-pair;
            int i_max = n-pair;
            for(int i = i_max; i >= i_min; --i) {
                // cout << "  i " << i << endl;

                int j_min = k-pair;
                int j_max = m-pair;

                for(int j = j_max; j >= j_min; --j) {
                    // cout << "    j " << j << endl;

                    // cout << " calc me nums1[i] * nums2[j] ";
                    // cout << " record max{me + [pair-1][i+1][j+1], [pair][i][j+1], [pair][i+1][j] " << endl;

                    long long a = (long long)nums1[i] * (long long)nums2[j];
                    dp[pair][i][j] = max({a + dp[pair-1][i+1][j+1], dp[pair][i][j+1], dp[pair][i+1][j]});



                }

            }
        }

        return dp[k][0][0];
    }
};
