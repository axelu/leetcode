
// 1017. Convert to Base -2
// https://leetcode.com/problems/convert-to-base-2/



// https://www.geeksforgeeks.org/convert-number-negative-base-representation/
class Solution {
public:
    string baseNeg2(int N) {
        // 0 <= N <= 10^9
        if( N == 0 ) return "0";

        string ans = "";
        int rem;
        while(N != 0) {
            // Get remainder by negative base, it can be
            // negative also
            rem = N % -2;
            N /= -2;

            // if remainder is negative, add abs(base) to
            // it and add 1 to n
            if( rem < 0 ) {
                rem += 2;
                N += 1;
            }

            // convert remainder to string add into the result
            ans = to_string(rem) + ans;
        }

        return ans;
    }
};
