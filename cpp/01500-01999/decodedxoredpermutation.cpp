
// 1734. Decode XORed Permutation
// https://leetcode.com/problems/decode-xored-permutation/




/*
 * how to go from:
 *     perm[0] ^ perm[1] = encoded[0],
 *               perm[1] ^ perm[2] = encoded[1],
 *                         perm[2] ^ perm[3] = encoded[2]
 *                                   ...
 *                                             perm[n-1] ^ perm[n] = encoded[n-1]
 * respectively:
 * perm[0] ^ perm[1] = encoded[0]
 * perm[1] ^ perm[2] = encoded[1]
 * perm[2] ^ perm[3] = encoded[2]
 * perm[3] ^ perm[4] = encoded[3]
 * x = perm[0] ^ perm[1] ^ perm[2] ^ perm[3] ^ perm[4]
 * order does not matter in XOR, XOR is associative, and we know it is a permutation between 1 and n, hence:
 * x = 1 ^ 2 ^ ... ^ n
 * back to: x = perm[0] ^ perm[1] ^ perm[2] ^ perm[3] ^ perm[4] => becomes
 *                        -----------------   -----------------
 *          x = perm[0] ^   encoded[1]      ^   encoded[3]         and so on, becomes
 *    perm[0] =    x    ^   encoded[1]      ^   encoded[3]
 *
 */
class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        // encoded.length == n - 1, 3 <= n < 1e5
        int n = encoded.size() + 1;

        vector<int> perm(n);

        // compute the XOR of the numbers between 1 and n, let it be x
        int x = 1;
        for(int i = 2; i <= n; ++i)
            x ^= i;

        // perm[0] = x XOR encoded[1] XOR encoded[3] XOR encoded[5] and so on
        for(int i = 1; i < n-1; i = i + 2)
            x ^= encoded[i];

        perm[0] = x;

        // perm[i] = perm[i-1] XOR encoded[i-1]
        for(int i = 1; i < n; ++i)
            perm[i] = perm[i-1] ^ encoded[i-1];

        return perm;
    }
};
