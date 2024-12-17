
// 3351. Sum of Good Subsequences
// https://leetcode.com/problems/sum-of-good-subsequences/




class Solution {
private:
    const long mod = 1000000007;

public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 1e5; 0 <= nums[i] <= 1e5

        pair<long,long> pre[100001]; // track key: val value: count, sum

        for(int i = 0; i < n; ++i) {
            long x = (long)nums[i];

            // how many arrive here from val-1?
            long pre_minus1_cnt = 0L;
            long pre_minus1_sum = 0L;
            if( x - 1 >= 0 ) {
                pre_minus1_cnt = pre[x-1].first;
                pre_minus1_sum = pre[x-1].second;
            }

            // how many arrive here from val+1?
            long pre_plus1_cnt = 0L;
            long pre_plus1_sum = 0L;
            if( x + 1 <= 100000 ) {
                pre_plus1_cnt = pre[x+1].first;
                pre_plus1_sum = pre[x+1].second;
            }

            // update pre
            long sum = x;   // just the current
            long cnt = 1L;  // just the current

            // pre-1
            sum = (sum + pre_minus1_sum) % mod;
            sum = (sum + ((x * pre_minus1_cnt) % mod)) % mod;
            cnt = (cnt + pre_minus1_cnt) % mod;

            // pre+1
            sum = (sum + pre_plus1_sum) % mod;
            sum = (sum + ((x * pre_plus1_cnt)) % mod) % mod;
            cnt = (cnt + pre_plus1_cnt) % mod;

            // cout << "i " << i << " x " << x << " cnt " << cnt << " sum " << sum << endl;
            pre[x] = {(pre[x].first + cnt) % mod, (pre[x].second + sum) % mod};
        }

        long ans = 0L;
        for(int i = 0; i <= 100000; ++i)
            ans = (ans + pre[i].second) % mod;

        return ans;
    }
};
