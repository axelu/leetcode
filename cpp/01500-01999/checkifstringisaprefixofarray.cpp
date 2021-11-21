
// 1961. Check If String Is a Prefix of Array
// https://leetcode.com/problems/check-if-string-is-a-prefix-of-array/





class Solution {
public:
    bool isPrefixString(string s, vector<string>& words) {

        string t = "";
        for(int i = 0; i < words.size(); ++i) {
            t += words[i];
            if( t == s )
                return true;
            if( t.size() >= s.size() )
                break;
        }

        return false;
    }
};
