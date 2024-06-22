
// 3121. Count the Number of Special Characters II
// https://leetcode.com/problems/count-the-number-of-special-characters-ii/




class Solution {
public:
    int numberOfSpecialChars(string word) {

        int upper[26];memset(upper,-1,sizeof upper);
        int lower[26];memset(lower,-1,sizeof lower);

        int n = word.size();
        for(int i = 0; i < n; ++i) {
            char c = word[i];
            if( islower(c) ) {
                int idx = c - 'a';
                lower[idx] = i;
            } else {
                int idx = c - 'A';
                if( upper[idx] == -1 )
                    upper[idx] = i;
            }
        }

        int ans = 0;

        for(int i = 0; i < 26; ++i)
            if( lower[i] != -1 && upper[i] != -1 && lower[i] < upper[i] )
                ++ans;

        return ans;
    }
};
