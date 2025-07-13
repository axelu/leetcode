
// 3602. Hexadecimal and Hexatrigesimal Conversion
// https://leetcode.com/problems/hexadecimal-and-hexatrigesimal-conversion/


class Solution {
private:
   char b16[16] = {'0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F'};

    // base16 encoding
    string base16encode(long num) {
        if( num == 0 ) return "0";
        string ans = "";
        long rem;
        while( num > 0 ) {
            rem = num % 16;
            ans = b16[rem] + ans;
            num /= 16;
        }
        return ans;
    }

    char b36[36] = {'0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',};

    // base36 encoding
    string base36encode(long num) {
        if( num == 0 ) return "0";
        string ans = "";
        long rem;
        while( num > 0 ) {
            rem = num % 36;
            ans = b36[rem] + ans;
            num /= 36;
        }
        return ans;
    }

public:
    string concatHex36(int n) {
        return base16encode(n*n) + base36encode(n*n*n);
    }
};
