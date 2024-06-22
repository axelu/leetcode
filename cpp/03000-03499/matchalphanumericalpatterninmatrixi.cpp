
// 3078. Match Alphanumerical Pattern in Matrix I
// https://leetcode.com/problems/match-alphanumerical-pattern-in-matrix-i/





class Solution {
public:
    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {
        int m = board.size();       // 1 <= board.length <= 50
        int n = board[0].size();    // 1 <= board[i].length <= 50

        int pm = pattern.size();
        int pn = pattern[0].size();

        // brute force
        for(int i = 0; i <= m - pm; ++i) {          // row on board, top left of pattern
            for(int j = 0; j <= n - pn; ++j) {      // col on board, top left of pattern

                int c2i[26];memset(c2i,-1,sizeof c2i);     // map of char to digit
                int i2c[10];memset(i2c,-1,sizeof i2c);     // map of digit to char
                bool f = true;
                for(int rb = i, rp = 0; rb < i + pm && f == true; ++rb, ++rp) {
                    for(int cb = j, cp = 0; cb < j + pn && f == true; ++cb, ++cp) {
                        char c = pattern[rp][cp];
                        if( isdigit(c) ) {
                            if( c - '0' != board[rb][cb] ) {
                                f = false;
                                break;
                            }

                        } else {
                            if( c2i[c - 'a'] == -1 && i2c[board[rb][cb]] == -1) {
                                c2i[c - 'a'] = board[rb][cb];
                                i2c[board[rb][cb]] = c - 'a';

                            } else if( c2i[c - 'a'] != board[rb][cb] || i2c[board[rb][cb]] != c - 'a' ) {
                                f = false;
                                break;
                            }
                        }
                    }
                }
                if( f )
                    return {i,j};
            }
        }


        return {-1,-1};
    }
};
