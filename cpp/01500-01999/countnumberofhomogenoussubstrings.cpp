
// 1759. Count Number of Homogenous Substrings
// https://leetcode.com/problems/count-number-of-homogenous-substrings/




class Solution {
public:
    int countHomogenous(string s) {
        int n = s.size();

        long mod = 1000000007;

        long ans = 0;

        long cnt = 1;
        for(int i = 1; i < n; ++i) {

            if( s[i-1] != s[i] ) {

                long t = cnt * (cnt + 1)/2;
                ans = (ans + t) % mod;

                cnt = 1;
                continue;
            }
            ++cnt;
        }
        // finish up
        long t = cnt * (cnt + 1)/2;
        ans = (ans + t) % mod;

        return ans;
    }
};
