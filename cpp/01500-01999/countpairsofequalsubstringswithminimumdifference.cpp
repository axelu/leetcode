
// 1794. Count Pairs of Equal Substrings With Minimum Difference
// https://leetcode.com/problems/count-pairs-of-equal-substrings-with-minimum-difference/




class Solution {
public:
    int countQuadruples(string firstString, string secondString) {
        int n1 = firstString.size();
        int n2 = secondString.size();

        int i;

        int i2[26]; // last aka highest index of a given char in secondString;
        for(i = 0; i < 26; ++i) i2[i] = -1;
        for(i = 0; i < n2; ++i) i2[secondString[i]-'a'] = i;

        int seen[26];memset(seen,0,sizeof seen);


        int j, res, mn = INT_MAX, ans = 0, cnt = 0;
        char c;
        for(i = 0; i < n1; ++i) {
            c = firstString[i]-'a';
            // get last index of firstString[i] in secondString
            if( seen[c] ) continue;
            seen[c] = 1; ++cnt;
            j = i2[c];
            if( j != -1 ) {
                res = i-j;
                if( res < mn ) {
                    mn  = res;
                    ans = 1;
                } else if( res == mn ) {
                    ++ans;
                }
            }
            if( cnt == 26 ) break;
        }

        return ans;
    }
};
