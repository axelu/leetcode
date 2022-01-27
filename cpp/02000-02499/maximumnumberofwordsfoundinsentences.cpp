
// 2114. Maximum Number of Words Found in Sentences
// https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/


class Solution {
public:
    int mostWordsFound(vector<string>& sentences) {
        int ans = 0;
        for(string& s : sentences) {
            int c = 0;
            for(int i = 0; i < s.size(); ++i) {
                if( s[i] == ' ' )
                    ++c;
            }
            ans = max(ans,c+1);
        }
        return ans;
    }
};
