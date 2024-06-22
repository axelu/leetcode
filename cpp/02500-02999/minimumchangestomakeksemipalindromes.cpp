
// 2911. Minimum Changes to Make K Semi-palindromes
// https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/





/* from the problem description:
 * A string with a length of len is considered a semi-palindrome,
 * if there exists a positive integer d such that 1 <= d < len and len % d == 0,
 * and if we take indices that have the same modulo by d, they form a palindrome.
 * For example, "aa", "aba", "adbgad", and,
 * "abab" are semi-palindrome and "a", "ab", and, "abca" are not.
 *
 * let us unpack how modulo behaves over a the indicies
 * len = 6 -> that gives us d {1,2,3} with constraints 1 <= d < len and len % d == 0
 *              0 1 2 3 4 5
 * d = 1  mod   0 0 0 0 0 0
 * d = 2  mod   0 1 0 1 0 1
 * d = 3  mod   0 1 2 0 1 2
 *
 */
class Solution {
private:
    int mem0[200][201];

    int solve(string& s, int begin, int len) {
        // returns the min number of letter changes
        // required to turn s into a semi-palindrome
        // 2 <= len and begin + len <= s.size()

        if( mem0[begin][len] != -1 )
            return mem0[begin][len];

        int ret = len % 2 == 0 ? len/2 : (len-1)/2; // worst case

        int end = begin + len;

        for(int d = 1; d <= len/2; ++d) {
            if( len % d != 0 )
                continue;

            int t = 0;
            for(int mod = 0; mod < d; ++mod) {
                int b = begin + mod;
                int e = end   - (d - mod);
                while(b < e) {
                    if( s[b] != s[e] )
                        ++t;
                    b += d;
                    e -= d;
                }
            }
            ret = min(ret,t);
            if( ret == 0 )
                break;
        }

        return mem0[begin][len] = ret;
    }

    int mem1[200][101];

    int rec(string& s, int n, int pos, int k) {
        if( k == 1 )
            return solve(s,pos,n-pos);

        if( mem1[pos][k] != -1 )
            return mem1[pos][k];

        // we create a substring starting at pos
        // with min len of 2
        // after us, basically starting from pos+len,
        // there must be the possibility to create
        // k-1 substrings with min len of s
        int mx_idx = n - (2 * (k-1));
        int l_max = mx_idx - pos;

        int ret = 200;

        for(int len = 2; len <= l_max; ++len) {
            ret = min(ret, solve(s,pos,len) + rec(s,n,pos+len,k-1));

        }

        return mem1[pos][k] = ret;
    }

public:
    int minimumChanges(string& s, int k) {
        int n = s.size(); // 2 <= s.length <= 200

        memset(mem0,-1,sizeof mem0);
        memset(mem1,-1,sizeof mem1);

        return rec(s,n,0,k);
    }
};
