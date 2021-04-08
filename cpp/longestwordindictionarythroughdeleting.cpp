
// 524. Longest Word in Dictionary through Deleting
// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
// day 22 February 2021 challenge
// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/



class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        int n = s.size();
        string ans = "";
        if( n == 0 ) return ans;

        int l,k;
        string word;
        for(int i = 0; i < d.size(); ++i) {
            word = d[i];
            l = word.size();
            if( l > n ) continue;
            k = 0;
            for(int j = 0; j < n; ++j)
                if( k < l && s[j] == word[k] ) ++k;
            if( k != 0 && k == l ) {
                if( ans.empty() ) {
                    ans = word;
                } else if( ans.size() < l ) {
                    ans = word;
                } else if( ans.size() == l ) {
                    if( word < ans ) ans = word;
                }
            }
        }

        return ans;
    }
};
