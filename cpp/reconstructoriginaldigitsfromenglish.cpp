
// 423. Reconstruct Original Digits from English
// https://leetcode.com/problems/reconstruct-original-digits-from-english/
// day 28 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3687/



/*
            0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
            a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    0 zero              1                             1        1                       1
    1 one               1                          1  1
    2 two                                             1              1        1
    3 three             2        1                                   1
    4 four                 1                          1        1        1
    5 five              1  1        1                                      1
    6 six                           1                             1              1
    7 seven             2                          1              1        1
    8 eight             1     1  1  1                                1
    9 nine              1           1              2
                        9  2  1  2  4              4  4        2  2  3  1  2  1  1     1
            a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
            0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

*/
class Solution {
public:
    string originalDigits(string s) {
        int n = s.size(); // n < 50000

        int cntS[26]; memset(cntS,0,sizeof cntS);
        // count the occurrence of each letter in s
        for(int i = 0; i < n; ++i)
            ++cntS[s[i]-'a'];

        int cntD[10];  memset(cntD,0,sizeof cntD);
        // count the occurrence of digts 0 to 9 in s
        // first we will count the digits that have a distinct letter
        // zero based on number of z's
        cntD[0]    = cntS[25]; // count  0's
        cntS[25]   = 0;        // deduct z
        cntS[4]   -= cntD[0];  // deduct e
        cntS[17]  -= cntD[0];  // deduct r
        cntS[14]  -= cntD[0];  // deduct o
        // two based on nunber of w's
        cntD[2]    = cntS[22]; // count  2's
        cntS[19]  -= cntD[2];  // deduct t
        cntS[22]   = 0;        // deduct w
        cntS[14]  -= cntD[2];  // deduct o
        // four based on number of u's
        cntD[4]    = cntS[20]; // count  4's
        cntS[5]   -= cntD[4];  // deduct f
        cntS[14]  -= cntD[4];  // deduct o
        cntS[20]   = 0;        // deduct u
        cntS[17]  -= cntD[4];  // deduct r
        // six based on number of x's
        cntD[6]    = cntS[23]; // count  6's
        cntS[18]  -= cntD[6];  // deduct s
        cntS[8]   -= cntD[6];  // deduct i
        cntS[23]   = 0;        // deduct x
        // eight based on number of g's
        cntD[8]    = cntS[6];  // count  8's
        cntS[4]   -= cntD[8];  // deduct e
        cntS[8]   -= cntD[8];  // deduct i
        cntS[6]    = 0;        // deduct g
        cntS[7]   -= cntD[8];  // deduct h
        cntS[19]  -= cntD[8];  // deduct t

        // left at this point are one, three, five, seven, nine
        // five based on number of f's
        cntD[5]    = cntS[5];  // count  5's
        cntS[5]    = 0;        // deduct f
        cntS[8]   -= cntD[5];  // deduct i
        cntS[21]  -= cntD[5];  // deduct v
        cntS[4]   -= cntD[5];  // deduct e
        // seven based on number of v's
        cntD[7]    = cntS[21]; // count  7's
        cntS[18]  -= cntD[7];  // deduct s
        cntS[4]   -= cntD[7];  // deduct e
        cntS[21]   = 0;        // deduct v
        cntS[4]   -= cntD[7];  // deduct e
        cntS[13]  -= cntD[7];  // deduct n
        // nine based on number of i's
        cntD[9]    = cntS[8];  // count  9's
        cntS[13]  -= cntD[9];  // deduct n
        cntS[8]    = 0;        // deduct i
        cntS[13]  -= cntD[9];  // deduct n
        cntS[4]   -= cntD[9];  // deduct e
        // one based on number of o's
        cntD[1]    = cntS[14]; // count  1's
        cntS[14]   = 0;        // deduct o
        cntS[13]  -= cntD[1];  // deduct n
        cntS[4]   -= cntD[1];  // deduct e
        // three based on number of t's
        cntD[3]    = cntS[19]; // count  9's
        cntS[19]   = 0;        // deduct t
        cntS[7]   -= cntD[3];  // deduct h
        cntS[17]  -= cntD[3];  // deduct r
        cntS[4]   -= cntD[3];  // deduct e
        cntS[4]   -= cntD[3];  // deduct e

        // at this point all cntS[i] should be 0

        string ans = "";
        for(int i = 0; i < 10; ++i)
            for(int j = 0; j < cntD[i]; ++j)
                ans += i+'0';
        return ans;
    }
};
