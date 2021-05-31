
// 1256. Encode Number
// https://leetcode.com/problems/encode-number/



/*   0          2^1 - 1
 *   1     0
 *   2     1
 *   3    00    2^2 - 1
 *   4    01
 *   5    10
 *   6    11
 *   7   000    2^3 - 1
 *   8   001
 *   9   010
 *  10   011
 *  11   100
 *  12   101
 *  13   110
 *  14   111
 *  15  0000    2^4 - 1
 *  16  0001
 *  17  0010
 *  ...
 *  10^9 11011100110101100101000000001
 */
class Solution {
private:
    int getNumberOfBinaryDigits(int num) {
        // 0 <= num <= 10^9
        for(int i = 1; i < 32; ++i)
            if( num < pow(2,i)-1 ) return i-1;
        return -1; // satisfy compiler
    }


public:
    string encode(int num) {
        int k = getNumberOfBinaryDigits(num);
        if( k == 0 ) return "";

        string ans = "";

        int d = num - ( pow(2,k) - 1 );
        for(int i = 0; i < k; ++i) {
            if( d & (1 << i ) ) ans.insert(ans.begin(),'1');
            else ans.insert(ans.begin(),'0');
        }

        return ans;
    }
};
