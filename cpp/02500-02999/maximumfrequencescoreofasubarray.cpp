
// 2524. Maximum Frequency Score of a Subarray
// https://leetcode.com/problems/maximum-frequency-score-of-a-subarray/




class Solution {
private:
    long mod = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x % mod
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a % mod
        return modPow(a,mod-2);
    }

    // modular division
    long modDivide(long a, long b) {
        // a = a % mod;
        long inv = modInverse(b);
        return (inv * a) % mod;
    }

public:
    int maxFrequencyScore(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<int,pair<int,long>> freq; // val, {cnt,val^cnt}

        long score = 0;
        long ans = 0;

        // sliding window
        int i = 0;          // left index
        for(int j = 0; j < n; ++j) {
            if( freq[nums[j]].first == 0 ) {
                // our score increases by nums[j];
                score = (score + nums[j]) % mod;
                freq[nums[j]].first = 1;
                freq[nums[j]].second = nums[j];
            } else {
                // our score increases by the difference of
                // (p.second * nums[j]) - p.second

                long t1 = (freq[nums[j]].second * nums[j]) % mod;
                long t2 = (t1 - freq[nums[j]].second) % mod;
                if( t2 < 0 )
                    t2 += mod;
                score = (score + t2) % mod;
                ++freq[nums[j]].first;
                freq[nums[j]].second = t1;
            }

            if( j - i + 1 == k ) {
                ans = max(ans,score);

                if( freq[nums[i]].first == 1 ) {
                    // our score decreases by nums[i]
                    score = (score - nums[i]) % mod;
                    if( score < 0 )
                        score += mod;
                    freq[nums[i]].first = 0;
                } else {
                    // our score decreases by the difference of
                    // p.second - (p.second / nums[i])
                    long t1 = modDivide(freq[nums[i]].second,nums[i]);
                    long t2 = (freq[nums[i]].second - t1) % mod;
                    if( t2 < 0 )
                        t2 += mod;
                    score = (score - t2) % mod;
                    if( score < 0 )
                        score += mod;
                    --freq[nums[i]].first;
                    freq[nums[i]].second = t1;
                }
                ++i;
            }
        }

        return ans;
    }
};
