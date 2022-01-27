
// 540. Base 7
// https://leetcode.com/problems/base-7/



class Solution {
public:
    string convertToBase7(int num) {
        if( num == 0 ) return "0";
        int sign = num < 0 ? -1 : 1;
        num *= sign;

        string ans = "";
        int rem;
        while( num > 0 ) {
            rem = num % 7;
            ans = to_string(rem) + ans;
            num /= 7;
        }
        if( sign == -1 ) ans = "-" + ans;
        return ans;
    }
};
