
// 1573. Number of Ways to Split a String
// https://leetcode.com/problems/number-of-ways-to-split-a-string/



class Solution {
public:
    int numWays(string s) {
        int n = s.size();

        int ones = 0;
        for(char c: s)
            if( c == '1' )
                ++ones;
        if( ones % 3 )
            return 0;

        long long mod = 1000000007;

        if( ones == 0 ) {
            long long ans = 0;
            for(long long i = 1; i <= n-2; ++i)
                ans = (ans + (n-i-1)) % mod;
            return ans;
        }

        //         0123456789
        // example 0110011011
        //           a  bc d
        long long a; // position of last 1 in part 0
        long long d; // position of 1st 1 in part 2
        long long b; // position of 1st 1 in part 1
        long long c; // position of last 1 in part 1

        int k = ones / 3;

        int i = 0;
        int p0ones = 0;
        while( true ) {
            if( s[i] == '1' )
                ++p0ones;
            if( p0ones == k )
                break;
            ++i;
        }
        a = i; // position of last 1 in part 0

        int j = n-1;
        int p2ones = 0;
        while( true ) {
            if( s[j] == '1' )
                ++p2ones;
            if( p2ones == k )
                break;
            --j;
        }
        d = j; // position of 1st 1 in part 2


        while( true ) {
            ++i;
            if( s[i] == '1' )
                break;
        }
        b = i; // position of 1st 1 in part 1

        while( true ) {
            --j;
            if( s[j] == '1' )
                break;
        }
        c = j; // position of last 1 in part 1

        return ((b-a) * (d-c)) % mod;
    }
};
