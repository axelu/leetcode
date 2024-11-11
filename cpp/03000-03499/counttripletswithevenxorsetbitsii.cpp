
// 3215. Count Triplets with Even XOR Set Bits II
// https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-ii/





/* goal is to find all triplets that after doing XOR have an even number of set bits
 * if we have 2 numbers with even set bits, after doing XOR we still have even number of set bits always
 * lets assume 4 set bits in each
 *     0 overlap 1 overlap 2 overlap 3 overlap 4 overlap
 *     11110000  11110000  11110000  11110000  11110000
 * XOR 00001111  00011110  00111100  01111000  11110000
 *     --------- --------- --------- --------- ---------
 *     11111111  11101110  11001100  10001000  00000000
 * if we have 2 numbers with odd set bits, after doing XOR we have even number of set bits always
 *
 * so we can combine number of set bits as follows
 * even even even
 * odd  odd  even
 * odd  even odd
 * even odd  odd
 */
class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    pair<int,int> countevenandoddsetbits(vector<int>& nums) {
        int even = 0;
        int odd  = 0;
        for(int i: nums) {
            int setbits = countSetBits(i);
            if( setbits % 2 )
                ++odd;
            else
                ++even;
        }
        return {even,odd};
    }

public:
    long long tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {

        auto p1 = countevenandoddsetbits(a);
        long long e1 = p1.first;
        long long o1 = p1.second;

        auto p2 = countevenandoddsetbits(b);
        long long e2 = p2.first;
        long long o2 = p2.second;

        auto p3 = countevenandoddsetbits(c);
        long long e3 = p3.first;
        long long o3 = p3.second;

        long long ans = 0LL;
        ans += e1 * e2 * e3;
        ans += o1 * o2 * e3;
        ans += o1 * e2 * o3;
        ans += e1 * o2 * o3;

        return ans;
    }
};
