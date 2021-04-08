
// 1816. Truncate Sentence
// https://leetcode.com/problems/truncate-sentence/


class Solution {
public:
    string truncateSentence(string s, int k) {
        int n = s.size();

        int c = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == ' ' ) {
                ++c;
                if( c == k ) {
                    string ans = s.substr(0,i);
                    return ans;
                }
            }
        }
        return s;
    }
};
