
// 3330. Find the Original Typed String I
// https://leetcode.com/problems/find-the-original-typed-string-i/




class Solution {
public:
    int possibleStringCount(string word) {
        int n = word.size();
        if( n == 1 )
            return 1;

        int ans = 1; // the word unchanged

        int consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( word[i] != word[i-1] ) {
                ans += consecutive - 1;
                consecutive = 1;
            } else {
                ++consecutive;
            }
        }
        // finish up
        ans += consecutive - 1;

        return ans;
    }
};
