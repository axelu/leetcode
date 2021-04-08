
// 293. Flip Game
// https://leetcode.com/problems/flip-game/



class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        size_t n = s.size();
        vector<string> ans;
        for(int i = 1; i < n; ++i)
            if( s[i-1] == '+' && s[i] == '+' ) {
                s[i-1] = '-';
                s[i] = '-';
                ans.push_back(s);
                // restore string
                s[i-1] = '+';
                s[i] = '+';
            }
        return ans;
    }
};
