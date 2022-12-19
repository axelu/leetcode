
// 2259. Remove Digit From Number to Maximize Result
// https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/




class Solution {
public:
    string removeDigit(string number, char digit) {
        int n = number.size();

        // if gain, chose leftmost
        // if no gain, chose rightmost loss

        // gain
        for(int i = 0; i < n-1; ++i)
            if( number[i] == digit && number[i+1] > number[i] ) {
                number.erase(i,1);
                return number;
            }

        // no gain
        for(int i = n-1; i >= 0; --i)
            if( number[i] == digit ) {
                number.erase(i,1);
                return number;
            }

        return ""; // satisfy compiler
    }
};
