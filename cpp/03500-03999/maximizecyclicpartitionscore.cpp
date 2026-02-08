
// 3743. Maximize Cyclic Partition Score
// https://leetcode.com/problems/maximize-cyclic-partition-score/


class Solution {
private:
    const long long INF = 2000000000001LL;

    /*
    // pos 1000, picks 1000, balance 2
    long long mem[1000][1001][3];
    // vector<vector<vector<long long>>> mem;

    long long rec(vector<int>& nums, int n, int pos, int picks, int balance, int k, int target_balance) {
        // cout << "rec pos " << pos << " picks " << picks << " balance " << balance << endl;
        if( pos == n || picks == 2*k )
            return balance == target_balance ? 0LL : -INF;

        if( mem[pos][picks][balance] != -1 ) {
        //    cout << "rec pos " << pos << " picks " << picks << " balance " << balance << " ret " << ret << endl;
            return mem[pos][picks][balance];
        }

        // we have a choice
        //     don't pick the current pos (skip) OR
        //     pick current pos as a min (if we can) OR
        //     pick current pos as a max (if we can)

        long long ret = rec(nums, n, pos+1, picks, balance, k, target_balance);
        if( balance > 0 )
            ret = max(ret, (long long)-nums[pos] + rec(nums, n, pos+1, picks+1, balance-1, k, target_balance));
        if( balance < 2 )
            ret = max(ret, (long long)nums[pos] + rec(nums, n, pos+1, picks+1, balance+1, k, target_balance));


        // cout << "rec pos " << pos << " picks " << picks << " balance " << balance << " ret " << ret << endl;
        // return ret;
        return mem[pos][picks][balance] = ret;
    }
    */

public:
    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return max(nums[0]-nums[1], nums[1]-nums[0]);

        // intuition: use DP
        // we can create up to k subarrays
        // in each subarray we pick the min and the max
        // range of subarray is max - min
        // score is sum of ranges, we are looking for the maximum score
        // in essence we pick up to 2*k values or up to n values, whatever is smaller
        //     if n is smaller, picks has to be even, if n is odd -> n-1 picks max
        // a value we pick is either assigned as a max or a min
        // we sum them up along the way
        // we always end up with even picks total, so either 2, 4, ..., 2*k
        // we can pick as follows
        //     max min min max
        //     max min max min
        //     min max min max
        //     min max max min
        // but because we can wrap around, this can become
        // min max min min max max
        // min max min max min max
        // min min max min max max
        // min min max max min max
        // or
        // max max min min max min
        // max max min max min min
        // max min max min max min
        // max min max max min min
        // let us assume a max is +1 and min is -1, we can track our picks
        // and when done we need to end with same balance we started with
        // in our original case, we start with 1
        //      1   2   3   4      1 2 3 4 5
        //     max min min max     1 2 1 0 1 (balance shown before pick)
        //     max min max min     1 2 1 2 1
        //     min max min max     1 0 1 0 1
        //     min max max min     1 0 1 2 1
        // now when we wrap around and start with a min, let us start with 2
        //  0   1   2   4   4   5  0 1 2 3 4 5 6
        // min max min min max max 2 1 2 1 0 1 2
        // min max min max min max 2 1 2 1 2 1 2
        // min min max min max max 2 1 0 1 0 1 2
        // min min max max min max 2 1 0 1 2 1 2
        // now when we wrap around and start with a max, let us start with 0
        //  0   1   2   4   4   5  0 1 2 3 4 5 6
        // max max min min max min 0 1 2 1 0 1 0
        // max max min max min min 0 1 2 1 2 1 0
        // max min max min max min 0 1 0 1 0 1 0
        // max min max max min min 0 1 0 1 2 1 0

        // worst case n = 1000, nums[i] = 1000000000
        //           1000000000000
        // LLONG_MAX 9223372036854775807

        // eliminate 3 or more consecutive dups
        auto it = nums.begin();
        advance(it,3);
        for(; it != nums.end();) {
            auto pre = prev(it);
            auto prepre = prev(pre);
            if( *pre == *it && *prepre == *it )
                it = nums.erase(it);
            else
                ++it;
        }
        n = nums.size(); // cout << n << endl;
        if( n == 2 )
            return max(nums[0]-nums[1], nums[1]-nums[0]);

        // max picks = min(2*k, n)
        // if max picks is odd, then -1
        int max_picks = min(2*k, n);
        if( max_picks % 2 )
            --max_picks;

        /*
        memset(mem, -1, sizeof mem);
        // vector<vector<vector<long long>>> mem(n, vector<vector<long long>>(max_picks+1, vector<long long>(3, -1L)));
        // mem.assign(n, vector<vector<long long>>(max_picks+1, vector<long long>(3, -1L)));
        long long a = rec(nums, n, 0, 0, 1, k, 1);
        memset(mem, -1, sizeof mem);
        // mem.assign(n, vector<vector<long long>>(max_picks+1, vector<long long>(3, -1L)));
        long long b = rec(nums, n, 0, 0, 2, k, 2);
        memset(mem, -1, sizeof mem);
        // mem.assign(n, vector<vector<long long>>(max_picks+1, vector<long long>(3, -1L)));
        long long c = rec(nums, n, 0, 0, 0, k, 0);
        return max({a, b, c});
        */

        // bottom up dp
        vector<vector<long long>> dp(3, vector<long long>(n, -INF));

        long long a = -INF;
        // 1 pick
        dp[2][n-1] =  nums[n-1];
        dp[0][n-1] = -nums[n-1];
        for(int i = n-2; i >= 0; --i) {
            dp[2][i] = max(dp[2][i+1], (long long)nums[i]);
            dp[0][i] = max(dp[0][i+1], (long long)-nums[i]);
        }
        for(int picks = 2; picks <= max_picks; ++picks) {
            if( picks % 2 == 0) {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    long long tmx =  x + dp[0][i+1]; // pos as max
                    long long tmn = -x + dp[2][i+1]; // pos as min
                    dp[1][i] = max({dp[1][i+1], tmx, tmn});
                }
                // dp[2].assign(n, -INF);
                // dp[0].assign(n, -INF);
                a = max(a, dp[1][0]);

            } else {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    // pos as max
                    dp[2][i] = max(dp[2][i+1], x + dp[1][i+1]);
                    // pos as min
                    dp[0][i] = max(dp[0][i+1], -x + dp[1][i+1]);
                }
                // dp[1].assign(n, -INF);

            }
        }

        dp[2].assign(n, -INF);
        dp[1].assign(n, -INF);
        dp[0].assign(n, -INF);

        // max ... min wrap arround
        long long b = -INF;
        // 1 pick
        dp[1][n-1] = -nums[n-1];
        for(int i = n-2; i >= 0; --i) {
            dp[1][i] = max(dp[1][i+1], (long long)-nums[i]);
        }
        for(int picks = 2; picks <= max_picks; ++picks) {
            if( picks % 2 == 0) {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    // pos as max
                    dp[2][i] = max(dp[2][i+1], x + dp[1][i+1]);
                    // pos as min
                    dp[0][i] = max(dp[0][i+1], -x + dp[1][i+1]);
                }
                // dp[1].assign(n, -INF);
                b = max(b, dp[2][0]);

            } else {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    long long tmx =  x + dp[0][i+1]; // pos as max
                    long long tmn = -x + dp[2][i+1]; // pos as min
                    dp[1][i] = max({dp[1][i+1], tmx, tmn});
                }
                // dp[2].assign(n, -INF);
                // dp[0].assign(n, -INF);

            }
        }

        dp[2].assign(n, -INF);
        dp[1].assign(n, -INF);
        dp[0].assign(n, -INF);

        // min ... max wrap around
        long long c = -INF;
        // 1 pick
        dp[1][n-1] = nums[n-1];
        for(int i = n-2; i >= 0; --i) {
            dp[1][i] = max(dp[1][i+1], (long long)nums[i]);
        }
        for(int picks = 2; picks <= max_picks; ++picks) {
            if( picks % 2 == 0) {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    // pos as max
                    dp[2][i] = max(dp[2][i+1], x + dp[1][i+1]);
                    // pos as min
                    dp[0][i] = max(dp[0][i+1], -x + dp[1][i+1]);
                }
                // dp[1].assign(n, -INF);
                c = max(c, dp[0][0]);

            } else {
                for(int i = n-picks; i >= 0; --i) {
                    long long x = nums[i];
                    long long tmx =  x + dp[0][i+1]; // pos as max
                    long long tmn = -x + dp[2][i+1]; // pos as min
                    dp[1][i] = max({dp[1][i+1], tmx, tmn});
                }
                // dp[2].assign(n, -INF);
                // dp[0].assign(n, -INF);

            }
        }

        return max({a, b, c});
    }
};
