
// 1545. Find Kth Bit in Nth Binary String
// https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/




/*
 * example: n = 4
 *   S1 = "0"
 *   S2 = "011"
 *   S3 = "0111001"
 *   S4 = "011100110110001"
 *         012345678901234
 *
 *  S1 = "0"
 *  Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
 *
 */
class Solution {
    char rec(vector<bool>& bs, int i, int k) {
        if( i > k-1 )
            return bs[k-1] ? '1' : '0';

        bs[i] = 1;
        for(int j = i-1; j >= 0; --j)
            bs[i + (i-j)] = !bs[j];

        return rec(bs,i+i+1,k);
    }
public:
    char findKthBit(int n, int k) {
        vector<bool> bs(pow(2,n) - 1);
        return rec(bs,1,k);
    }
};
