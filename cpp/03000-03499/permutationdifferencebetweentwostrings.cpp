
// 3146. Permutation Difference between Two Strings
// https://leetcode.com/problems/permutation-difference-between-two-strings/




class Solution {
public:
    int findPermutationDifference(string s, string t) {
        int n = s.size(); // s.size() == t.size()

        int sidx[26];memset(sidx,-1,sizeof sidx);
        int tidx[26];memset(tidx,-1,sizeof tidx);
        for(int i = 0; i < n; ++i) {
            sidx[s[i]-'a'] = i;
            tidx[t[i]-'a'] = i;
        }

        int ans = 0;
        for(int i = 0; i < 26; ++i) {
            ans += abs(sidx[i] - tidx[i]);



        }

        return ans;
    }
};
