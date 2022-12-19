
// 2315. Count Asterisks
// https://leetcode.com/problems/count-asterisks/




class Solution {
public:
    int countAsterisks(string s) {
        int ans = 0;
        int bar = 0;
        for(char c: s)
            if( c == '|' )
                ++bar;
            else if( c == '*' && bar % 2 == 0 )
                ++ans;

        return ans;
    }
};
