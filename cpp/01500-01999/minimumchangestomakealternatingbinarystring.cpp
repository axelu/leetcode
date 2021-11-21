
// 1758. Minimum Changes To Make Alternating Binary String
// https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/



class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        int s0 = 0, s1 = 0; // number of changes if we start with 0 or 1

        for(int i = 0; i < n; ++i) {
            if( i%2 == 0 ) {
                // i is even
                // for the case that we started with a 0, we expect 0
                if( s[i] == '1' ) ++s0;
                // for the case that we started with a 1, we expect 1
                if( s[i] == '0' ) ++s1;
            } else {
                // i is odd
                // for the case that we started with a 0, we expect 1
                if( s[i] == '0' ) ++s0;
                // for the case that we started with a 1, we expect 0
                if( s[i] == '1' ) ++s1;
            }
        }
        return min(s0,s1);
    }
};
