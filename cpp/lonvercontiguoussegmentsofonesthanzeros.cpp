
// 1869. Longer Contiguous Segments of Ones than Zeros
// https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/




class Solution {
public:
    bool checkZeroOnes(string s) {
        int n = s.size();
        if( n == 1 ) return s[0] == '1';

        int l0 = 0; // lenght of longest contiguous segment of 1s
        int l1 = 0; // lenght of longest contiguous segment of 0s

        int t0 = 0;
        int t1 = 0;
        if( s[0] == 0 ) t0 = 1;
        else t1 = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] != s[i] ) {
                // some sequence ended and a new one is starting
                if( s[i] == '0' ) {
                    // sequence of 1s ended
                    l1 = max(l1,t1);
                    t0 = 0;
                } else {
                    // sequence of 1s ended
                    l0 = max(l0,t0);
                    t1 = 0;
                }
            }
            if( s[i] == '1' ) ++t1;
            else ++t0;
        }
        // finish up
        l1 = max(l1,t1);
        l0 = max(l0,t0);

        return l1 > l0;
    }
};
