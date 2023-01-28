
// 2450. Number of Distinct Binary Strings After Applying Operations
// https://leetcode.com/problems/number-of-distinct-binary-strings-after-applying-operations/



class Solution {
private:
    long MOD = 1000000007;

    int modular_pow(unsigned long long base, int exponent) {
        unsigned long long c = 1;
        for(int i = 0; i < exponent; ++i)
            c = (c * base) % MOD;
        return c;
    }

public:
    int countDistinctStrings(string s, int k) {
        // s itself does not matter, only its length
        // what we actually have is a perfect binary tree
        // at which we calculate the number of leaf nodes

        return modular_pow(2,s.size() - k + 1);
    }
};
