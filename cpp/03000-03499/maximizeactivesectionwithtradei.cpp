
// 3499. Maximize Active Section with Trade I
// https://leetcode.com/problems/maximize-active-section-with-trade-i/


/* 01234567890123456789
  1100100111001110111111
         xxx
       -------


 */
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        if( n == 1 )
            return s[0] == '1' ? 1 : 0;

        int ans = 0;

        vector<array<int,3>> v; // sections 0 type either 0 or 1, start, end

        int i = 0;
        for(int j = 0; j < n; ++j) {
            if( s[j] == '1' )
                ++ans;

            if( s[i] != s[j] ) {
                // we are starting a new section
                int t = s[i] - '0';
                v.push_back({t, i, j-1});
                i = j;
            }
        }
        // finish up
        v.push_back({(int)(s[i]-'0'), i, n-1});

        // ans has number of 1s in s,
        // basically our answer if we couldn't convert anything

        int mx_gain = 0;

        int v_sz = v.size();

        for(int i = 0; i < v_sz; ++i) {
            // are we in a block of 1's?
            if( v[i][0] == 1 ) {
                // is our block of 1's sourrounded by 0's?
                int zeros_left = 0;
                if( i > 0 ) {
                    zeros_left = v[i-1][2] - v[i-1][1] + 1;
                }
                int zeros_right = 0;
                if( i < v_sz-1 ) {
                    zeros_right = v[i+1][2] - v[i+1][1] + 1;
                }

                if( zeros_left != 0 && zeros_right != 0 )
                    mx_gain = max(mx_gain, zeros_left + zeros_right);
            }
        }


        return ans + mx_gain;
    }
};
