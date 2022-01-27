
// 1375. Number of Times Bianry String Is Prefix-Aligned
// https://leetcode.com/problems/number-of-times-binary-string-is-prefix-aligned/



class Solution {
public:
    int numTimesAllBlue(vector<int>& flips) {
        int n = flips.size();

        int s[n+1];memset(s,0,sizeof s); // status of bit
        s[0] = 1;
        int l[n+1];memset(l,0,sizeof l); // status of bits to the left
        l[0] = 1;

        int ans = 0;

        for(int i = 1; i <= n; ++i) {
            int b = flips[i-1];
            // set bit b
            s[b] = 1;
            if( l[b-1] ) {
                l[b] = 1;
                for(int j = b+1; j <= n; ++j) {
                    if( s[j] )
                        l[j] = 1;
                    else
                        break;
                }
            }
            if( l[i] )
                ++ans;
        }

        return ans;
    }
};
