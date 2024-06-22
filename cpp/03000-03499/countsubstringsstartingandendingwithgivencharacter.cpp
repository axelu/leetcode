
// 3084. Count Substrings Starting and Ending with Given Character
// https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/



class Solution {
public:
    long long countSubstrings(string s, char c) {
        long long n = 0LL;
        for(char chr: s)
            if( chr == c )
                ++n;

        return n * (n + 1)/2;
    }
};
