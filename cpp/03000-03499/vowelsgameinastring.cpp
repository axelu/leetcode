
// 3227. Vowels Game in a String
// https://leetcode.com/problems/vowels-game-in-a-string/



class Solution {
public:
    bool doesAliceWin(string s) {
        // vowels
        // odd      Alice wins (Alice removes the entire string)
        // even     Alice wins (ALice removes all but 1 vowel)
        // 0        Bob wins (Alice cannot remove anything)

        int cnt = 0;
        for(char c: s) {
            if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' )
                ++cnt;
        }

        return cnt == 0 ? false : true;
    }
};
