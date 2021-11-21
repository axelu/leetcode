
// 1903. Largest Odd Number in String
// https://leetcode.com/problems/largest-odd-number-in-string/



class Solution {
public:
    string largestOddNumber(string num) {
        // find the rightmost odd number
        int i = num.size()-1;
        for(; i >= 0; --i)
            if( num[i] %2 != 0 )
                break;

        if( i == -1 )
            return "";

        return num.substr(0,i+1);
    }
};
