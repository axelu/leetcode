
// 3120. Count the Number of Special Characters I
// https://leetcode.com/problems/count-the-number-of-special-characters-i/




class Solution {
public:
    int numberOfSpecialChars(string word) {

        int upper[26];memset(upper,0,sizeof upper);
        int lower[26];memset(lower,0,sizeof lower);

        for(char c: word)
            if( islower(c) )
                ++lower[c - 'a'];
            else
                ++upper[c - 'A'];

        int ans = 0;

        for(int i = 0; i < 26; ++i)
            if( upper[i] && lower[i] )
                ++ans;

        return ans;
    }
};
