
// 1234. Replace the Substring for Balanced String
// https://leetcode.com/problems/replace-the-substring-for-balanced-string/




class Solution {
public:
    int balancedString(string s) {
        int n = s.size(); // multiple of four

        int q_cnt = 0, w_cnt = 0, e_cnt = 0, r_cnt = 0;
        for(char c: s)
            if( c == 'Q' )
                ++q_cnt;
            else if( c == 'W' )
                ++w_cnt;
            else if( c == 'E' )
                ++e_cnt;
            else // c == 'R'
                ++r_cnt;

        int ans = 0;

        int q_exc = q_cnt - n/4;
        int w_exc = w_cnt - n/4;
        int e_exc = e_cnt - n/4;
        int r_exc = r_cnt - n/4;

        if( q_exc > 0 || w_exc > 0 || e_exc > 0 || r_exc > 0 ) {
            ans = INT_MAX;

            // sliding window
            int q = 0, w = 0, e = 0, r = 0;
            int i = 0;
            for(int j = 0; j < n; ++j) {
                if( s[j] == 'Q' )
                    ++q;
                else if( s[j] == 'W' )
                    ++w;
                else if( s[j] == 'E' )
                    ++e;
                else // s[j] == 'R'
                    ++r;

                if( q >= q_exc && w >= w_exc && e >= e_exc && r >= r_exc ) {
                    // we have a window [i,j] that we could make s balanced with
                    // ans = min(ans, j - i + 1);

                    // shrink the window
                    while( q >= q_exc && w >= w_exc && e >= e_exc && r >= r_exc ) {
                        ans = min(ans, j - i + 1);
                        if( s[i] == 'Q' )
                            --q;
                        else if( s[i] == 'W' )
                            --w;
                        else if( s[i] == 'E' )
                            --e;
                        else // s[i] == 'R'
                            --r;
                        ++i;
                    }
                }
            }
        }

        return ans;
    }
};
