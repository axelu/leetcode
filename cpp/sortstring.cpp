
// 1370. Increasing Decreasing String
// https://leetcode.com/problems/increasing-decreasing-string/



class Solution {
public:
    string sortString(string s) {
        auto n = s.size();
        if( n == 1 ) return s;

        int chars[26]; memset(chars,0,sizeof chars);
        for(char ch : s) ++chars[ch - 'a'];

        string r = "";
        while(n > 0) {
            for(int i = 0; i < 26; ++i)
                if( chars[i] > 0 ) {
                    r += (i + 'a');
                    --chars[i];
                    --n;
                }
            for(int i = 25; i >= 0; --i)
                if( chars[i] > 0 ) {
                    r += (i + 'a');
                    --chars[i];
                    --n;
                }
        }

        return r;
    }
};
