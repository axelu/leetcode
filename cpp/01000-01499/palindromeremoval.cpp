
// 1246. Palindrome Removal
// https://leetcode.com/problems/palindrome-removal/


class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return 1;
        if( n == 2 )
            return arr[0] == arr[1] ? 1 : 2;

        int dp[n][n];memset(dp,0,sizeof dp);
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;

        // sliding a window of length 2 over arr
        for(int i = 0; i < n-1; ++i)
            dp[i][i+1] = arr[i] == arr[i+1] ? 1 : 2;

        for(int l = 3; l <= n; ++l) {
            for(int i = 0; i <= n - l; ++i) {   // left index
                int j = i + l - 1;              // right index

                int a =  INT_MAX;
                if( arr[i] == arr[j] ) {
                    a = arr[i+1] == arr[j-1] ? dp[i+1][j-1] : 1 + dp[i+1][j-1];
                    if( l > 3 ) {
                        // left [i+1][k], right [k+1][j-1]
                        // if either left or right a have same end, we can
                        // combine in one transaction

                        for(int k = i+1; k <= j-1; ++k) {
                            // left
                            if( arr[i+1] == arr[k] )
                                a = min(a,dp[i+1][k] + dp[k+1][j-1]);
                            // right
                            if( arr[k+1] == arr[j-1] )
                                a = min(a,dp[i+1][k] + dp[k+1][j-1]);
                        }
                    }
                }

                for(int k = i; k <= j-1; ++k)
                    a = min(a,dp[i][k] + dp[k+1][j]);

                dp[i][j] = a;
            }
        }

        return dp[0][n-1];
    }
};
