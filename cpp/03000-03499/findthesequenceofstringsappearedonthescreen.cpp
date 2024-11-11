
// 3324. Find the Sequence of Strings Appeared on the Screen
// https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/


class Solution {
public:
    vector<string> stringSequence(string target) {
        vector<string> ans;

        string s = "";
        int s_sz = 0;

        for(char c: target) {
            s.append(1,'a');
            ++s_sz;
            ans.push_back(s);

            while( s[s_sz-1] != c ) {
                if( s[s_sz-1] != 'z' )
                    ++s[s_sz-1];
                else
                    s[s_sz-1] = 'a';
                ans.push_back(s);
            }
        }

        return ans;
    }
};
