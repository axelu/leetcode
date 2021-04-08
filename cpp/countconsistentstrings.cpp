
// 1684. Count the Number of Consistent Strings
// https://leetcode.com/problems/count-the-number-of-consistent-strings/

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int allowd[26];memset(allowd,0,sizeof allowd);
        for(char c : allowed)
            allowd[c-'a'] = 1;

        int ans = 0;
        for(string s : words) {
            ++ans;
            for(char c : s) {
                if( !allowd[c-'a'] ) {
                    --ans;
                    break;
                }
            }
        }
       return ans;
    }
};
