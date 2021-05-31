
// 1138. Alphabet Board Path
// https://leetcode.com/problems/alphabet-board-path/



class Solution {
public:
    string alphabetBoardPath(string target) {
        string ans = "";
        int i,j;     // target position
        int x=0,y=0; // current position
        int idx,d,s,k;
        for(k = 0; k < target.size(); ++k) {
            idx = target[k]-'a';
            i = idx/5;
            j = idx%5;
            if( i > x ) { // going down
                d = j-y;
                if( d < 0 ) // going left
                    for(s = 0; s < -d; ++s) ans += 'L';
                else         // going right
                    for(s = 0; s < d; ++s) ans += 'R';
                d = i-x;
                for(s = 0; s < d; ++s) ans += 'D';
            } else {        // going up or staying in same row
                d = x-i;
                for(s = 0; s < d; ++s) ans += 'U';
                d = j-y;
                if( d < 0 ) // going left
                    for(s = 0; s < -d; ++s) ans += 'L';
                else         // going right
                    for(s = 0; s < d; ++s) ans += 'R';
            }
            x = i; y = j;
            ans += '!';
        }
        return ans;
    }
};
