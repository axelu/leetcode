
// 520. Detect Capital
// https://leetcode.com/problems/detect-capital/




class Solution {
public:
    bool detectCapitalUse(string word) {
        int n = word.size();
        if( n == 1 ) return true;

        // case1: All letters in this word are capitals
        // case2: All letters in this word are not capitals
        // case3: Only the first letter in this word is capital

        int cse;
        if( isupper(word[0]) && isupper(word[1]) )
            cse = 1;
        else if( islower(word[0]) && islower(word[1]) )
            cse = 2;
        else if( isupper(word[0]) && islower(word[1]) )
            cse = 3;
        else
            return false;
        cout << cse << endl;
        for(int i = 2; i < n; ++i) {
            if( cse == 1 ) {
                if( islower(word[i]) ) return false;
            } else {
                if( isupper(word[i]) ) return false;
            }
        }
        return true;
    }
};
