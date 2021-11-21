
// 1538. Guess the Majority in a Hidden Array
// https://leetcode.com/problems/guess-the-majority-in-a-hidden-array/





/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares 4 different elements in the array
 *     // return 4 if the values of the 4 elements are the same (0 or 1).
 *     // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 *     // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *     int query(int a, int b, int c, int d);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
private:
    int n,cnta,posa,cntb,posb;

    void cnt(ArrayReader &reader, int i, int a, int b, int c) {
        int t;
        for(; i < n; ++i) {
            t = reader.query(a,b,c,i);
            // t has to be 4 or 2
            if( t == 4 )
                ++cnta;
            else {
                ++cntb;
                posb = i;
            }
        }
    }

    void solve(ArrayReader &reader) {
        // start with idx 0,1,2,3
        int t = reader.query(0,1,2,3);
        if( t == 4 ) {
            // // elements 0,1,2 and 4 are equal
            posa = 0;
            cnta = 4;
            cnt(reader,4,0,1,2);

        } else if( t == 2 ) {
            int t2 = reader.query(0,1,2,4);
            if( t2 == 4 ) {
                // elements 0,1,2 and 4 are equal
                posa = 0;
                cnta = 4;
                posb = 3;
                cntb = 1;
                cnt(reader,5,0,1,2);
                return;
            }

            int t3 = reader.query(1,2,3,4);
            if( t3 == 4 ) {
                // elements 1,2,3,4 are equal
                posa = 1;
                cnta = 4;
                posb = 0;
                cntb = 1;
                cnt(reader,5,1,2,3);
                return;
            }

            int t4 = reader.query(0,1,3,4);
            if( t4 == 4 ) {
                // elements 0,1,3,4 are equal
                posa = 0;
                cnta = 4;
                posb = 2;
                cntb = 1;
                cnt(reader,5,0,1,3);
                return;
            }

            int t5 = reader.query(0,2,3,4);
            if( t5 == 4 ) {
                // elements 0,2,3,4 are equal
                posa = 0;
                cnta = 4;
                posb = 1;
                cntb = 1;
                cnt(reader,5,0,2,3);
                return;
            }

            if( t3 == 2 ) {
                // elements 1,2,3 are equal; elements 0,4 are equal
                posa = 1;
                cnta = 3;
                posb = 0;
                cntb = 2;
                cnt(reader,5,1,2,3);
                return;
            }

            if( t2 == 2 ) {
                // elements 0,1,2 are equal; elements 3,4 are equal
                posa = 0;
                cnta = 3;
                posb = 3;
                cntb = 2;
                cnt(reader,5,0,1,2);
                return;
            }

            if( t4 == 0 ) {
                // elements 0,2,3 are the equal, elements 1,3 are equal
                posa = 0;
                cnta = 3;
                posb = 1;
                cntb = 2;
                cnt(reader,5,0,2,3);
                return;
            }

            // only one case left
            // elements 0,1,3 are the equal, elements 2,3 are equal
            posa = 0;
            cnta = 3;
            posb = 2;
            cntb = 2;
            cnt(reader,5,0,1,3);
            return;

        } else {
            // t == 0

            int t2 = reader.query(1,2,3,4); // if 0 we know id0 and id4 are equal
            int t3 = reader.query(0,2,3,4); // if 0 we know id1 and id4 are equal

            if( t2 == 0 && t3 == 0 ) {
                // elements 0,1,4 are equal, elements 2,3 are equal
                posa = 0;
                cnta = 3;
                posb = 2;
                cntb = 2;
                cnt(reader,5,0,1,4);
                return;
            }

            if( t2 == 2 && t3 == 2 ) {
                // elements 0,1 are equal, elements 2,3,4 are equal
                posa = 2;
                cnta = 3;
                posb = 0;
                cntb = 2;
                cnt(reader,5,2,3,4);
                return;
            }

            int t4 = reader.query(0,1,2,4);
            if( t3 == 0 && t4 == 0 ) {
                // elements 1,3,4 are equal, elements 0,2 are equal
                posa = 1;
                cnta = 3;
                posb = 0;
                cntb = 2;
                cnt(reader,5,1,3,4);
                return;
            }

            if( t3 == 2 && t4 == 2 ) {
                // elements 0,2,4 are equal, elements 1,3 are equal
                posa = 0;
                cnta = 3;
                posb = 1;
                cntb = 2;
                cnt(reader,5,0,2,4);
                return;
            }

            if( t2 == 0 && t4 == 0 ) {
                // elements 0,3,4 are equal, elements 1,2 are equal
                posa = 0;
                cnta = 3;
                posb = 1;
                cntb = 2;
                cnt(reader,5,0,3,4);
                return;
            }

            // only one case left
            // t2 == 2 and t4 == 2
            // elements 1,2,4 are equal, elements 0,3 are equal
            posa = 1;
            cnta = 3;
            posb = 0;
            cntb = 2;
            cnt(reader,5,1,2,4);

        }
    }

public:
    int guessMajority(ArrayReader &reader) {
        n = reader.length(); // 5 <= nums.length <= 10^5
        // if n is even, there could be a tie (ans could be -1)
        // if n is odd, there cannot be a tie

        cnta = 0; posa = -1;
        cntb = 0; posb = -1;

        solve(reader);

        if( cnta > cntb )
            return posa;
        else if( cnta < cntb )
            return posb;
        else
            return -1;
    }
};
