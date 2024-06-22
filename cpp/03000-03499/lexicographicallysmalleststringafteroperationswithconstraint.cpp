
// 3106. Lexicographically Smallest String After Operations With Constraint
// https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/




/*       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
 *       a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
 *  0 a  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1
 *  1 b  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2
 *  2 c  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3
 *  3 d  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4
 *  4 e  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5
 *  5 f  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6
 *  6 g  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7
 *  7 h  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8
 *  8 i  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9
 *  9 j  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10
 * 10 k 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11
 * 11 l 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13 12
 * 12 m 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12 13
 * 13 n 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11 12
 * 14 o 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10 11
 * 15 p 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9 10
 * 16 q 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8  9
 * 17 r  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7  8
 * 18 s  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6  7
 * 19 t  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5  6
 * 20 u  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4  5
 * 21 v  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3  4
 * 22 w  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2  3
 * 23 x  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1  2
 * 24 y  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0  1
 * 25 z  1  2  3  4  5  6  7  8  9 10 11 12 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 *
 * the maximum difference we can have between 2 chars is 13
 * example s = "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn", k = 1300
 * ans = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
 * example s = "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn", k = 1299
 * ans = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"

*/
class Solution {
private:
    int distance(string s, string t, int n, vector<int>& distances) {
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            int a = s[i] - 'a';
            int b = t[i] - 'a';
            int t = abs(a-b);
            int rem = (26-t) % 26;
            int d = min(t, rem);
            sum += d;
            distances[i] = d;
        }
        return sum;
    }
public:
    string getSmallestString(string s, int k) {
        int n = s.size();

        string t(n,'a');
        vector<int> distances(n);
        int d = distance(s,t,n,distances);
        // cout << "d " << d << endl;

        int i = n - 1;
        while( i >= 0 && d > k ) {
            if( s[i] == 'a' ) {
                --i;
                continue;
            }

            // assume we make the char in s and t at position i equal
            int d_new = d - distances[i];
            if( d_new >= k ) {
                t[i] = s[i];

            } else {
                // we can back paddle some
                char c = s[i];
                while( d_new < k ) {
                    --c;
                    ++d_new;
                }
                t[i] = c;
            }
            d = d_new;
            --i;
        }

        return t;
    }
};
