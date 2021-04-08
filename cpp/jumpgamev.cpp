
// 1340. Jump Game V
// https://leetcode.com/problems/jump-game-v/


class Solution {
private:
    size_t n;
    vector<int> * Arr;
    int D;
    int * Dp;

    int jump(int i) {

        if( Dp[i] != 0 ) return Dp[i];

        int r = 0;
        int cur = (*Arr)[i];
        int j;
        bool lft = true, rgt = true;
        for(int x = 1; x <= D; ++x) {
            // i + x -> go right
            j = i + x;
            if( j < n && rgt ) {
                if( cur <= (*Arr)[j] )
                    rgt = false;
                else
                    r = max(r,jump(j));
            }
            // i - x -> go left
            j = i - x;
            if( j >= 0 && lft ) {
                if( cur <= (*Arr)[j] )
                    lft = false;
                else
                    r = max(r,jump(j));
            }
        }

        return Dp[i] = 1 + r;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        if( n == 1 ) return 1;

        int dp[n];
        for(int i = 0; i < n; ++i) dp[i] = 0;
        Dp = dp;

        Arr = &arr;
        D = d;

        for(int i = 0; i < n; ++i) jump(i);

        return *max_element(dp,dp+n);
    }
};
