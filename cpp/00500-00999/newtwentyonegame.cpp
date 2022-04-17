
// 837. New 21 Game
// https://leetcode.com/problems/new-21-game/




class Solution {
private:
    double rec(int n, int k, int maxPts, int r, double mem[]) {
        if( r >= k ) {
            return r <= n ? 1 : 0;
        }

        if( mem[r] != -1.0 )
            return mem[r];

        double f = 1/(double)maxPts;
        double ret = 0.0;
        for(int i = 1; i <= maxPts; ++i) {
            ret += f * rec(n,k,maxPts,r+i,mem);
        }

        return mem[r] = ret;
    }

public:
    double new21Game(int n, int k, int maxPts) {
        // 0 <= k <= n <= 10^4

        // there is no game if k == 0,
        // so we will always have points <= n
        if( k == 0 )
            return 1.0; // propability 100%

        // if it takes more than one roll to get from
        // k-1 to n, then we will always arrive
        // at lower/equal n
        if( k - 1 + maxPts <= n )
            return 1.0;

        // we need to cover the range were we arrived at
        // k-1 and roll maxPts
        // example: n = 21, k = 17, maxPtx = 10
        // max we could arrive at: k - 1 + maxPts = 17 - 1 + 10 = 26

        /*
        // top down TLE
        double mem[n+1];
        for(int i = 0; i <= n; ++i)
            mem[i] = -1.0;
        return rec(n,k,maxPts,0,mem);
        */

        /*
        // bottom up TLE
        double ans = 0.0;
        double f = 1/(double)maxPts;
        // let dp[i] be the propability of arriving at a sum of i
        double dp[n+1];
        // we know we start the game with 0 pts,
        // so probability is 100% for dp[0]
        dp[0] = 1.0;
        for(int i = 1; i <= n; ++i) {
            dp[i] = 0.0;
            // we can arrive at current i from whereever we were before
            // and having rolled between 1 and maxPts
            // so like i = (prior) + (roll)
            //         i = (i - 1)  + 1  <- we rolled a 1
            //         i = (i - 2)  + 2  <- we rolled a 2
            //         ...
            // our prior position had to be at least 0 (start of game) and
            // because we stop rolling at k, our prior position had
            // to be less than k
            for(int j = max(1,i-(k-1)); j <= maxPts && i-j >= 0; ++j)
                dp[i] += f * dp[i-j];

            // collect ans
            if( i >= k )
                ans += dp[i];
        }
        */

        // bottom up sliding window
        double ans = 0.0;
        double f = 1/(double)maxPts;
        // let dp[i] be the propability of arriving at a sum of i
        double dp[n+1];
        // we know we start the game with 0 pts,
        // so probability is 100% for dp[0]
        dp[0] = 1.0;
        // slide a window of size maxPts over the range till the
        // right side of the window reaches n
        double window_sum = 1.0;
        for(int i = 1; i <= n; ++i) {
            dp[i] = 0.0;

            dp[i] = f * window_sum;

            if( i < k )
                window_sum += dp[i];

            // subtract from our window sum
            // what falls outside the window
            if( i - maxPts >= 0 )
                window_sum -= dp[i-maxPts];

            // collect ans
            if( i >= k )
                ans += dp[i];
        }

        return ans;
    }
};
