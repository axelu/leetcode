
// 3803. Count Residue Prefixes
// https://leetcode.com/problems/count-residue-prefixes/



class Solution {
public:
    int residuePrefixes(string s) {
        int freq[26]; memset(freq, 0, sizeof freq);
        int distinct = 0;
        int ans = 0;
        for(int i = 0; i < s.size(); ++i) {
            char c = s[i];
            ++freq[c-'a'];
            if( freq[c-'a'] == 1 )
                ++distinct;
            if( distinct == (i+1) % 3 )
                ++ans;
        }
        return ans;
    }
};
