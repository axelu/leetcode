
// 3031. Minimum Time to Revert Word to Initial State II
// https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-ii/




// initialize once
long long p_pow[1000001];
bool init = false;

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        const int p = 31;
        const int m = 1e9 + 9;

        if( !init ) {
            init = true;
            p_pow[0] = 1;
            for (int i = 1; i < 1000001; i++)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        // calculate hash value of word
        int n = word.size();
        if( k == n )
            return 1;
        long long h_s[n+1];
        h_s[0] = 0LL;
        for(int i = 0; i < n; i++)
            h_s[i+1] = (h_s[i] + (word[i] + 1) * p_pow[i]) % m;

        // worst case
        // if n % k == 0 -> n/k
        // else n/k + 1
        // the question is, can we do better?

        // rolling hash
        for(int i = k, round = 1; i < n; i += k, ++round) {
            // is word.substr(i) a prefix of word?
            long long cur_h = (h_s[n] + m - h_s[i]) % m;
            if (cur_h == h_s[n-i] * p_pow[i] % m)
                return round;
        }

        return n % k == 0 ? n/k : n/k + 1;
    }
};
