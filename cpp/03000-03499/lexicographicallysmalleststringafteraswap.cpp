
// 3216. Lexicographically Smallest String After a Swap
// https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/




class Solution {
public:
    string getSmallestString(string s) {
        int n = s.size();

        for(int i = 0; i < n-1; ++i) {
            if( s[i] % 2 == s[i+1] % 2 && s[i] > s[i+1] ) {
                int t = s[i+1];
                s[i+1] = s[i];
                s[i] = t;
                break;
            }
        }

        return s;
    }
};
