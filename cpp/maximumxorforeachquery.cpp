
// 1829. Maximum XOR for Each Query
// https://leetcode.com/problems/maximum-xor-for-each-query/




class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int n = nums.size();

        // answer for a prefix is the XOR of that prefix XORed with 2^(maximumBit)-1
        // 1 <= maximumBit <= 20
        int mx = pow(2,maximumBit)-1;

        // a ^ b = c
        // in our case this translates to:
        // pxor[i+1] ^ k = 2^(maximumBit)-1
        // because a ^ b = c also fullfills a ^ c = b, we can solve to
        // pxor[i+1] ^ 2^(maximumBit)-1 = k

        int i;
        vector<int> ans(n);
        int pxor[n+1]; // prefix xor
        pxor[0] = 0;
        for(i = 0; i < n; ++i) {
            pxor[i+1] = nums[i] ^ pxor[i];
            ans[n-1-i] = pxor[i+1] ^ mx;
        }

        return ans;
    }
};
