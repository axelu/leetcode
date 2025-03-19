
// 3413. Maximum Coins From K Consecutive Bags
// https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/





class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        int n = coins.size();

        sort(begin(coins), end(coins));
        map<int, pair<int,char>> mp; // key: index on our number line value: {index in coins, begin or end}
        vector<long long> prefixSum(n+1, 0LL);
        for(int i = 0; i < n; ++i) {
            int l = coins[i][0];
            int r = coins[i][1];
            mp.insert({l, {i, 'b'}});
            mp.insert({r, {i, 'e'}});

            long long t = (long long)(r - l + 1) * (long long)coins[i][2];
            prefixSum[i+1] = prefixSum[i] + t;
        }

        long long ans = 0LL;

        // lets line up k begin with each begin of an interval and k end with each end of an interval
        for(int i = 0; i < n; ++i) {
            // k begin at begin of interval
            int k_end = coins[i][0] + k - 1;
            auto f1 = mp.lower_bound(k_end);
            if( f1 == mp.end() ) {
                // we encompass everything starting at our current interval
                // till including the last interval
                ans = max(ans, prefixSum[n] - prefixSum[i]);
            } else {
                if( f1->second.second == 'b' ) {
                    // we encompass all intervals including f1->second.first-1
                    int end_interval_idx = f1->second.first;
                    long long t = prefixSum[end_interval_idx] - prefixSum[i];

                    if( f1->first == k_end ) {
                        // we encompass also 1 bag of f1->second.first
                        t += (long long)coins[end_interval_idx][2];
                    }

                    ans = max(ans, t);

                } else {
                    // we encompass all intervals including f1->second.first-1
                    // and some portion of f1->second.first
                    int end_interval_idx = f1->second.first;
                    long long t = prefixSum[end_interval_idx] - prefixSum[i];

                    t += (long long)(k_end - coins[end_interval_idx][0] + 1) * (long long)coins[end_interval_idx][2];

                    ans = max(ans, t);
                }
            }

            // k end at end of interval
            int k_begin = coins[i][1] - k + 1;
            auto f2 = mp.lower_bound(k_begin);
            // f2 will always be != mp.end()
            if( f2->second.first == i ) {
                // we cover some portion of our current interval, maybe all
                if( f2->second.second == 'e' ) {
                    ans = max(ans, (long long)k * (long long)coins[i][2]);
                } else {
                    // we cover our current interval completely
                    ans = max(ans, (long long)(coins[i][1] - coins[i][0] + 1) * (long long)coins[i][2]);
                }
            } else {
                if( f2->second.second == 'e' ) {
                    int begin_interval_idx = f2->second.first;
                    long long t = prefixSum[i+1] - prefixSum[begin_interval_idx+1];

                    t += (long long)(f2->first - k_begin + 1) * coins[begin_interval_idx][2];
                    ans = max(ans, t);

                } else {
                    int begin_interval_idx = f2->second.first;
                    long long t = prefixSum[i+1] - prefixSum[begin_interval_idx];
                    ans = max(ans, t);
                }
            }
        }

        return ans;
    }
};
