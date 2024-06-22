
// 440. K-th Smallest in Lexicographical Order
// https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/


/* example n = 32, k = 15
 * integers in the range [1,32] in lexicographically order
 *     1 1
 *     2 10
 *     3 11
 *     4 12
 *     5 13
 *     6 14
 *     7 15
 *     8 16
 *     9 17
 *    10 18
 *    11 19
 *    12 2
 *    13 20
 *    14 21
 * x  15 22
 *    16 23
 *    17 24
 *   ...
 * we are looking for the 15th smallest integer
 * we see that 22 is our answer
 *
 * let us assume we have a function f(prefix,n) that gives us the number of integers in 
 *     range [prefix,n] inclusive with a prefix 'prefix'
 * we start with a prefix of 1
 * f(1,32) = 11 -> [1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
 * because 11 < 15, we know our answer is not in the current prefix, so we need to increase our prefix -> prefix = prefix + 1
 * at the same time tough, because we know there are already 11 numbers in front, we are now no longer looking
 * for the 15th smallest integer, but the 15 - 11 = 4th smallest integer
 * increase prefix by 1 -> 1 + 1 = 2
 * decrease k by 11 -> 15 - 11 = 4
 * f(2,32) = 11 -> [2, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]
 *                             x
 * because 11 >= 4, we know our answer is in the current prefix, so we need to lengthen our prefix -> prefix = prefix * 10 to 'add' a 0 at the end
 * at the same time though, as we are basically taking the 1st number (= our current prefix) off the list, we are now no longer looking
 * for the 4th smallest number, but the 3rd smallest number
 * lengthen prefix 2 -> 20 respectively 2 * 10 = 20
 * decrease k by 1 -> 4 - 1 = 3
 * f(20,32) = 1 -> [20]
 * repeat following the same rules at this point
 * because 1 < 3, incease prefix 20 + 1 = 21, decrease k by 1 3 - 1 = 2
 * f(21,32) = 1 -> [21]
 * because 1 < 2, incease prefix 21 + 1 = 22, decrease k by 1 2 - 1 = 1
 * because k == 1, we know the current prefix is the answer -> 22
 * 
 * key observation:
 * if the prefix is NOT a prefix of n, all prefix counts for (prefix * 10) + i with 0 <= i < 10 return the same result
 * this is our needed optimization to get the processing time down
 */
class Solution {
private:
    
    bool is_prefix(int prefix, int n) {
        string str_prefix = to_string(prefix);
        string str_n = to_string(n);
        // str_prefix.size() <= str_n.size()
        for(int i = 0; i < str_prefix.size(); ++i)
            if( str_prefix[i] != str_n[i] )
                return false;
        return true;
    }
    
    int f(long prefix, int n) {
        // returns the number of integers in range [prefix, n] inclusive with a prefix 'prefix'
        if( prefix > n ) 
            return 0;
        
        //cout << "f " << prefix << " n " << n << endl;

        int ret = 1;
        if( !is_prefix(prefix,n) ) {
            ret += 10 * f(prefix * 10, n);
        } else {
            for(int i = 0; i < 10; ++i) 
                ret += f(prefix * 10 + i, n);
        }
        
        //cout << "f " << prefix << " n " << n << " " << ret << endl;
        return ret;
    }
    
public:
    int findKthNumber(int n, int k) {
        
        int prefix = 1; // start with a prefix of 1
        while( k != 1 ) {
            int count = f(prefix, n);
            // cout << "k " << k << " f(" << prefix << ", " << n << ") = " << count << endl;
            if( count < k ) {
                prefix = prefix + 1;
                k = k - count;
            } else {
                prefix = prefix * 10;
                k = k - 1;
            }
        }
        
        return prefix;
    }
};







// 43 / 69 test cases passed, then TLE 1/25/2024

class Solution {
private:
    int ans;
    long n,k;

    void rec(long i, int& x) {

        if( x == k ) {
            ans = i;
            return;
        }

        int i_limit = i == 1 ? 9 : i + 9;
        if( n <= i_limit ) {
            for(; i <= i_limit; ++i) {
                if( x == k ) {
                    ans = i;
                    break;
                }
                ++x;
                if( i == n )
                    break;
            }

        } else {
            for(; i <= i_limit; ++i) {
                if( x == k ) {
                    ans = i;
                    break;
                }
                ++x;
                if( i == n )
                    break;

                if( i * 10L <= n )
                    rec(i * 10L, x);
                if( ans != -1 )
                    break;
            }
        }

        return;
    }

public:
    int findKthNumber(int n, int k) {
        this->n = n;
        this->k = k;

        ans = -1;
        int x = 1;
        rec(1L,x);

        return ans;
    }
};
