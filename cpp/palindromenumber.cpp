#include <iostream>
#include <cassert>

// https://leetcode.com/problems/palindrome-number/

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
    
        if ( x < 0 ) return false;
        if ( x < 10 ) return true;

        int o = x;
        long int r = 0;
        while ( x > 0 ) {

            r = (r * 10) + (x % 10);
            x /= 10;

        }
        return ( r == o ) ? true : false;
    }
};

int main() {

    Solution s;

    assert(s.isPalindrome(121) == true);
    assert(s.isPalindrome(-121) == false);
    assert(s.isPalindrome(10) == false);
    assert(s.isPalindrome(9) == true);
    assert(s.isPalindrome(2147483647) == false);
    assert(s.isPalindrome(-2147483648) == false);
    assert(s.isPalindrome(2147447412) == true);

    /*
    for ( int i = 0; i <= 2147483647; i++) {
        if (s.isPalindrome(i)) cout << i << endl;
    }
    */


    return 0;
}
