
// 3835. Count Subarrays With Cost Less Than or Equal to K
// https://leetcode.com/problems/count-subarrays-with-cost-less-than-or-equal-to-k/




class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        long long ans = 0;

        // sliding window
        map<int,int> mp;
        int last_j = -1;
        long long mx, mn, len, last_len, cost, a, b;
        int i = 0;                   // left index
        for(int j = 0; j < n; ++j) { // right index
            ++mp[nums[j]];

            mx  = mp.rbegin()->first;
            mn  = mp.begin()->first;
            len = j - i + 1;
            cost = (mx-mn) * len;

            if( cost > k ) {
                // take stock of
                // all subarrays between i..j-1, respectively
                // total number of subarrays for an array of length len-1
                a = (len - 1) * len/2;
                // DON'T DOUBLE COUNT !!!
                last_len = (last_j - i);
                b = last_len * (last_len + 1)/2;
                ans += a - b;

                last_j = j;

                // shrink the window
                while( cost > k ) {
                    --mp[nums[i]];

                    if( mp[nums[i]] == 0 )
                        mp.erase(nums[i]);

                    ++i;

                    mx  = mp.rbegin()->first;
                    mn  = mp.begin()->first;
                    len = j - i + 1;
                    cost = (mx-mn) * len;
                }
            }
        }
        // finish up
        len = n - i + 1;
        a = (len - 1) * len/2;
        // DON'T DOUBLE COUNT !!!
        last_len = (last_j - i);
        b = last_len * (last_len + 1)/2;
        ans += a - b;

        return ans;
    }
};
