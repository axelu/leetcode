
// Binary Gap
// https://leetcode.com/problems/binary-gap/


class Solution {
public:
    int binaryGap(int N) {
        // 1 <= N <= 10^9 -> max length of binary = 31
        // cout << bitset<31>(N).to_string() << endl;

        int r = 0;
        int c = 0;

        bool count = false;
        // string R;
        while( N > 0 ) {
            int rem = N % 2;
            if( rem == 0 ) {
                if( count ) ++c;
            } else {
                if( count ) {
                    ++c;
                    r = max(r, c);
                    c = 0;
                }
                count = true;
            }
            // R = ( N % 2 == 0 ? "0" : "1" ) + R;
            N /= 2;
        }

        // cout << R << endl;

        return r;
    }
};
