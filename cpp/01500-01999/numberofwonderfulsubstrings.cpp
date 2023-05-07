
// 1915. Number of Wonderful Substrings
// https://leetcode.com/problems/number-of-wonderful-substrings/




class Solution {
private:
    long long getdiff1(unordered_map<int,long long>& um, int mask) {
        // unordered_map<int,long long> um; // mask, count
        // returns the sum of count for all um[x], where
        // there is exactly in bit different between x and mask

        long long ret = 0;

        for(int i = 0; i < 10; ++i) {

            int t = mask ^ (1 << i);
            ret += um[t];
        }

        return ret;
    }

public:
    long long wonderfulSubstrings(string word) {
        int n = word.size();

        // word consists of lowercase English letters from 'a' to 'j'.
        // 0123456789
        // abcdefghij

        // at each n we will do a 'prefixSum':
        //   if we have an even number of the current char, the bit char-'a' will be one, else 0
        // initially the char count of all chars is zero, and zero is even
        //                                      jihgfedcba
        int mask = pow(2,10)-1; // 1023, binary 1111111111

        unordered_map<int,long long> um; // mask, count
        ++um[mask];

        long long ans = 0;

        for(int i = 1; i <= n; ++i) {

            // calculate the current mask
            //   by toggle bit in prev mask
            int bit = word[i-1] - 'a';
            mask ^= 1 << bit;

            // get number of masks that differ by exactly one bit
            ans += getdiff1(um,mask);
            // get the number of equal masks
            ans += um[mask];

            ++um[mask];
        }

        return ans;
    }
};
