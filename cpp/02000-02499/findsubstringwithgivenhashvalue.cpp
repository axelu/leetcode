
// 2156. Find Substring With Given Hash Value
// https://leetcode.com/problems/find-substring-with-given-hash-value/






class Solution {
private:

    long long hash(string pattern, long long p_pow[], int modulo) {
        int S = pattern.size();
        long long h_s = 0;
        for (int i = 0; i < S; i++)
            h_s = (h_s + ((pattern[i]-'a') + 1) * p_pow[i]) % modulo;

        return h_s;
    }

public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        int n = s.size();

        long long p_pow[n+1];
        p_pow[0] = 1LL;
        for(int i = 1; i <= n; ++i)
            p_pow[i] = (p_pow[i-1] * (long long)power) % modulo;

        // rolling hash
        long long h[n+1];
        h[0] = 0LL;
        for(int i = 0; i < n; ++i) {
            int c = s[i]-'a';
            h[i+1] = (h[i] + (c + 1) * p_pow[i]) % modulo;

            if( i+1 >= k ) {
                long long cur_h = (h[i+1] + modulo - h[i+1-k]) % modulo;
                if (cur_h == hashValue * p_pow[i+1-k] % modulo) {
                    // double check for collision
                    string ans = s.substr(i+1-k, k);
                    long long h_s = hash(ans, p_pow, modulo);
                    if( h_s == hashValue )
                        return ans;
                }
            }
        }

        return ""; // we should never get here
    }
};
