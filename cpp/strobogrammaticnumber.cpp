
// 246. Strobogrammatic Number
// https://leetcode.com/problems/strobogrammatic-number/



class Solution {
public:
    bool isStrobogrammatic(string num) {
        size_t n = num.size();
        if( 0 == n ) return true;

        string t = "";
        for(int i = n-1; i >= 0; --i) {
            if( num[i] == '1' )
                t += '1';
            else if( num[i] == '6' )
                t += '9';
            else if( num[i] == '8' )
                t += '8';
            else if( num[i] == '9' )
                t += '6';
            else if( num[i] == '0' )
                t += '0';
            else
                return false;
        }

        return t == num;
    }
};
