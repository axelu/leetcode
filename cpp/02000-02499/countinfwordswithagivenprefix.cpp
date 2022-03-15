
// 2185. Counting Words With a Given Prefix
// https://leetcode.com/problems/counting-words-with-a-given-prefix/


class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int ans = 0;
        int pref_n = pref.size();
        for(string& s : words)
            if( s.size() >= pref_n && s.substr(0,pref_n) == pref)
                ++ans;

        return ans;
    }
};
