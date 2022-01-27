
// 738. Monotone Increasing Digits
// https://leetcode.com/problems/monotone-increasing-digits/





class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        if( n < 10 )
            return n;

        int i = 1;
        int f = 1;
        int rem;

        int prev = n%10;
        n /= 10;

        int ans = prev;

        while( n > 0 ) {
            ++i;
            f *= 10;
            rem = n%10;
            //cout << rem << " i " << i << " f " << f << endl;

            if( rem > prev ) {
                ans = f-1;
                ans += (rem-1)*f;
                prev = rem-1;
            } else {
                ans += rem*f;
                prev = rem;
            }

            n /= 10;
        }

        return ans;
    }
};
