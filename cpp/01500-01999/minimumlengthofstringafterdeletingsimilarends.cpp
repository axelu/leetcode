
// 1750. Minimum Length of String After Deleting Similar Ends
// https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/



class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();

        int i = 0;      // left idx
        int j = n-1;    // right idx

        while( i < j && s[i] == s[j] ) {

            // advance left
            // peek ahead
            while( i+1 < j && s[i+1] == s[i] )
                ++i;

            // advance right
            // peek ahead
            while( j-1 > i && s[j-1] == s[j] )
                --j;

            ++i;
            --j;
        }

        return j-i+1;;
    }
};
