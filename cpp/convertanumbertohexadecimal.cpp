
// 405. Convert a Number to Hexadecimal
// https://leetcode.com/problems/convert-a-number-to-hexadecimal/




class Solution {
public:
    string toHex(int num) {
        if( num == 0 ) return "0";
        string ans = "";
        long n = num < 0 ? 4294967296L + (long)num : long(num);
        long rem;
        while( n > 0 ) {
            rem = n % 16L;
            if( rem > 9L )
                ans.insert(ans.begin(),'W' + rem);
            else
                ans = to_string(rem) + ans;
            n /= 16L;
        }
        return ans;
    }
};
