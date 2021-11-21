#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// 8. String to Integer (atoi)
// https://leetcode.com/problems/string-to-integer-atoi/

class Solution {
public:
    int myAtoi(string str) {

        if ( str.empty() ) {
            return 0;
        } else if ( str.size() == 1 ) {
            return _charToInt(str[0]);
        } else {

            // character classes
            //    whitespace, sign, zero-digit, non-zero-digit
            // modes
            //    0 accept whitespace or sign or non-zero-digit or zero-digit
            //    1 accept non-zero-digit
            //    2 accept zero-digit or non-zero-digit

            int INT_MN = -2147483648;
            int INT_MX = 2147483647;

            vector<char> v;
            int nbr_digits = 0;
            int sign = 1;
            int mode = 0;
            for (auto it = str.begin(); it != str.end(); it++) {
                const char c = *it;
                if ( mode == 0 ) {
                // accept whitespace or sign or non-zero-digit
                    if ( _isSign(c) ) {
                        if ( c == '-' ) sign = -1;
                        mode = 1;
                    } else if ( _isZeroDigit(c) ) {
                        mode = 1;
                    } else if ( _isNonZeroDigit(c) ) {
                        v.push_back(c);
                        nbr_digits++;
                        mode = 2;
                    } else if ( !_isWhiteSpace(c) ) {
                        return 0;
                    }
                } else if ( mode == 1 ) {
                // accept non-zero-digit, ignore zero-digit
                    if ( _isNonZeroDigit(c) ) {
                        v.push_back(c);
                        nbr_digits++;
                        mode = 2;
                    } else if ( _isZeroDigit(c) ) {
                        continue;
                    } else {
                        return 0;
                    }
                } else {
                // accept zero-digit or non-zero-digit
                    // short circuit if more digits than 2^31 int OR
                    // if same number digits as 2^31 int but 1st nbr > 2
                    if ( _isZeroDigit(c) || _isNonZeroDigit(c) ) {
                        if ( (nbr_digits == 9 && _charToInt(v[0]) > 2) || \
                              nbr_digits == 10 ) {
                            if ( sign == 1 ) {
                                return INT_MX;
                            } else {
                                return INT_MN;
                            }
                        }
                        v.push_back(c);
                        nbr_digits++;
                   } else {
                       break;
                   }
                }
            }
       
            if ( v.empty() ) {
                return 0;
            } else if ( v.size() == 1 ) {
                return _charToInt(v[0]) * sign;
            } else {
                int exp = v.size() - 1;
                int r = 0;

                for (int i = 0; i < v.size(); i++) {
                    int t = _charToInt(v[i]) * pow(10, exp) * sign;
                    if ( sign == 1 ) {
                        if ( t <= INT_MX - r ) {
                            r = r + t;
                        } else {
                            return INT_MX;
                        }
                    } else {
                        if ( t >= INT_MN - r ) {
                            r = r + t;
                        } else {
                            return INT_MN;
                        }
                    }
                    exp--;
                }

                return r;
            }
        }
    }
private:
    bool _isWhiteSpace(const char & c) {
        return ( c == ' ' ) ? true : false;
    }

    bool _isSign(const char & c) {
        return ( c == '-' || c == '+' ) ? true : false;
    }

    bool _isZeroDigit(const char & c) {
        return ( c == '0' ) ? true : false;
    }

    bool _isNonZeroDigit(const char & c) {
        bool r;
        
        switch(c) {
            case '1': r = true;
                      break;
            case '2': r = true;
                      break;
            case '3': r = true;
                      break;
            case '4': r = true;
                      break;
            case '5': r = true;
                      break;
            case '6': r = true;
                      break;
            case '7': r = true;
                      break;
            case '8': r = true;
                      break;
            case '9': r = true;
                      break;
            default: r = false;
                      break;
        }
        
        return r;
    }

    int _charToInt(const char & c) {
        int r;
        
        switch(c) {
            case '1': r = 1;
                      break;
            case '2': r = 2;
                      break;
            case '3': r = 3;
                      break;
            case '4': r = 4;
                      break;
            case '5': r = 5;
                      break;
            case '6': r = 6;
                      break;
            case '7': r = 7;
                      break;
            case '8': r = 8;
                      break;
            case '9': r = 9;
                      break;
            default: r = 0;
                      break;
        }
        
        return r;
    }
};


int main() {

    Solution s;

    string str;

    assert(s.myAtoi(str) == 0);

    str = "";
    assert(s.myAtoi(str) == 0);
   
    str = " ";
    assert(s.myAtoi(str) == 0);

    str = "9";
    assert(s.myAtoi(str) == 9);

    str = "0";
    assert(s.myAtoi(str) == 0);
   
    str = "+";
    assert(s.myAtoi(str) == 0);
    
    str = "-";
    assert(s.myAtoi(str) == 0);
    
    str = "a";
    assert(s.myAtoi(str) == 0);
    
    str = "    a";
    assert(s.myAtoi(str) == 0);
    
    str = "  ";
    assert(s.myAtoi(str) == 0);

    str = " +";
    assert(s.myAtoi(str) == 0);

    str = " -";
    assert(s.myAtoi(str) == 0);

    str = " +0";
    assert(s.myAtoi(str) == 0);

    str = " -0";
    assert(s.myAtoi(str) == 0);

    str = "  09";
    assert(s.myAtoi(str) == 9);

    str = "  0000000000012345678";
    assert(s.myAtoi(str) == 12345678);
   
    str = "   000+";
    assert(s.myAtoi(str) == 0);

    str = "   +00009";
    assert(s.myAtoi(str) == 9);

    str = "  9";
    assert(s.myAtoi(str) == 9);
    
    str = "  +9";
    assert(s.myAtoi(str) == 9);
    
    str = "  -9";
    assert(s.myAtoi(str) == -9);
    
    str = "  +9 ";
    assert(s.myAtoi(str) == 9);
    
    str = "  -9b";
    assert(s.myAtoi(str) == -9);
    
    str = "-91283472332";
    assert(s.myAtoi(str) == -2147483648);
    
    str = "91283472332";
    assert(s.myAtoi(str) == 2147483647);
    
    str = "-9128347233";
    assert(s.myAtoi(str) == -2147483648);
    
    str = "9128347233";
    assert(s.myAtoi(str) == 2147483647);
    
    str = "42";
    assert(s.myAtoi(str) == 42);
    
    str = "+42";
    assert(s.myAtoi(str) == 42);
    
    str = "   -42";
    assert(s.myAtoi(str) == -42);
    
    str = "4193 with words";
    assert(s.myAtoi(str) == 4193);
    
    str = "words and 987";
    assert(s.myAtoi(str) == 0);
    
    str = "-2147483648";
    assert(s.myAtoi(str) == -2147483648);
    
    str = "-2147483640";
    assert(s.myAtoi(str) == -2147483640);
    
    str = "2147483647";
    assert(s.myAtoi(str) == 2147483647);
    
    str = "-2147483649";
    assert(s.myAtoi(str) == -2147483648);
    
    str = "2147483648";
    assert(s.myAtoi(str) == 2147483647);
    
    return 0;
}
