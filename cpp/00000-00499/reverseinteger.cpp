#include <iostream>
#include <limits>
#include <queue>
#include <cmath>


// 7. Reverse Integer
// https://leetcode.com/problems/reverse-integer/

using namespace std;

class Solution {
public:
    int reverse(int x) {

        // using math only, 
        // other options would include conversions to string or similar

        // 32-bit signed int
        // min -2147483648
        // max 2147483647

        // preemting edge cases 
        if ( x > -10 && x < 10 ) return x;

        // preemting on system with 32-bit signed int implementation
        // on systems where int is implemented > 32-bit, this would make tests fail
        // if ( x <= -2147483648 || x >= 2147483647 ) return 0;
        if ( x < -2147483641 || x > 2147483641 ) return 0;

        int n = ( x < 0 ) ? -1 : 1;
        x = x * n;

        queue<int> d;
        int f;
        int c = 0;
        bool queue_zeros = false;
        while ( x > 0 ) {
            int m =  x % 10;
            if ( m > 0 ) queue_zeros = true;
            if ( queue_zeros ) {
                d.push(m);
                f = pow(10,c); c++;
            }
            x = x / 10;
        }

        bool danger_zone = false;
        if ( f == 1000000000 ) {
            if ( d.front() > 2 ) {
                return 0;
            } else if ( d.front () == 2) {
                danger_zone = true;
                d.pop();
                f = f / 10;
            }
        }

        int r = 0;
        while ( !d.empty() ) {
            r = r + ( d.front() * f );
            d.pop();
            f = f / 10;
        }

        if ( danger_zone ) {
            if ( r > 147483647 ) {
                return 0;
            } else {
                r = r + 2000000000;
            }
        }

        return r * n;
    }
};


int main() {

    Solution s;

    // input shall be a 32-bit signed integer
    // if reveresed int < -2^31 or > 2^31 -1 then return 0
    // 2^31 = 2,147,483,648 hence -2147483648 to 2147483647
    int input;

    // input = 123;
    // expect 321
    
    // input = -123;
    // expect -321
    
    // input = 120;
    // expect 21

    // input = -120;
    // expect -21
    
    // input = -1000;
    // expect -1

    // input = 2147483647;
    // expect 0

    // input = -2147483648;
    // expect 0

    // input = 1001;
    // expect 1001

    // input = 10010;
    // expect 1001
    
    // input = 2147447412; + and -
    // expect 2147447412

    cout << "sizeof(int) " << sizeof(int) << " bytes" << endl;
    cout << "numeric_limits<int>::min() " << numeric_limits<int>::min() << endl; // -2147483648
    cout << "numeric_limits<int>::max() " << numeric_limits<int>::max() << endl; // 2147483647


    // cout << s.reverse(2147483646) << endl;

    int b = 0;
    for (int i = -2147483648; i <= 0; i++) {
        int r = s.reverse(i);
        // if ( r == 0 || r == i ) cout << "i = " << i << " r = " << r << endl;
        // if ( r == i ) cout << "i = " << i << " r = " << r << endl;
        if ( r != 0 ) cout << "i = " << i << " r = " << r << endl;

        if ( b == 100 ) break;
        b++;
    }

    b = 0;
    for (int i = 2147483647; i >= 0; i--) {
        int r = s.reverse(i);
        // if ( r == 0 || r == i ) cout << "i = " << i << " r = " << r << endl;
        // if ( r == i ) cout << "i = " << i << " r = " << r << endl;
        if ( r != 0 ) cout << "i = " << i << " r = " << r << endl;

        if ( b == 100 ) break;
        b++;
    }
    
    return 0;
}
