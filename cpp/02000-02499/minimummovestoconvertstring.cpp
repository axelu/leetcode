
// 2027. Minimum Moves to Convert String
// https://leetcode.com/problems/minimum-moves-to-convert-string/





class Solution {
public:
    int minimumMoves(string s) {
        int n = s.size();
        int ans = 0;

        // slide a window of length 3 over s
        // when the left most position of window is X, we convert
        for(int i = 0; i < n-3; ++i) {

            if( s[i] != 'X' )
                continue;

            ++ans;
            // did we reach into the last 3?
            if( i >= n-5 ) {
                s[i+1] = 'O';
                s[i+2] = 'O';
            }

            i += 2; // loop will advance i by 1 more

        }
        // finish up
        if( s[n-3] == 'X' || s[n-2] == 'X' || s[n-1] == 'X')
            ++ans;

        return ans;
    }
};
