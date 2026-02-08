
// 3747. Count Distinct Integers After Removing Zeros
// https://leetcode.com/problems/count-distinct-integers-after-removing-zeros/


/*
 * permuation => order matters
 * permutation with repetition formula n^r
 *    n number of items to chose from
 *    r how many items to choose
 *
 */


// initialize once
long long p9[16];
long long ps[16];
bool init = false;

class Solution {
public:
    long long countDistinct(long long n) {
        // 1 <= n <= 1e15 = 1000000000000000

        // we can precalculate part of the result
        // we have at most 16 digits
        // let d be the number of digits in n
        // we can calculate the result for integer where we have d-1 9's
        // at each position we get 9^position additional distinct integers
        // note 1-indexed
        //  15 14 13 12 11 10  9  8  7  6  5  4  3   2    1   0
        //                                     9^3  9^2 9^1
        //                       and so on ... 729   81   9
        if( !init ) {
            p9[1] = 9LL;
            ps[1] = 9LL;
            for(int i = 2; i < 16; ++i) {
                p9[i] = p9[i-1] * 9LL;
                ps[i] = ps[i-1] + p9[i];
            }
            init = true;
        }

        long long ans = 0LL;
        if( n <= 9 )
            return n;

        // brute force
        /*
        for(int i = 1; i <= n; ++i) {
            string t = to_string(i);
            if( t.contains('0') )
                continue;
            cout << i << endl;
            ++ans;
        }
        return ans;
        */

        string s = to_string(n);
        int digits = s.size();
        for(int i = 0; i < digits; ++i) {
            if( s[i] == '0' )
                break;

            if( i == digits-1 ) {
                ans += (long long)(s[i]-'0');
                break;
            }

            int p = (digits-1) - i;
            long long f = (long long)(s[i]-'0') - 1LL;

            ans += f * p9[p];
        }

        return ps[digits-1] + ans;
    }
};
