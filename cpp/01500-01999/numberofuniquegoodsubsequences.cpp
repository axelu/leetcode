
// 1987. Number of Unique Good Subsequences
// https://leetcode.com/problems/number-of-unique-good-subsequences/



class Solution {
public:
    int numberOfUniqueGoodSubsequences(string& binary) {
        int n = binary.size();
        if( n == 1 )
            return 1;

        long MOD = 1000000007;

        // we can have subseqences that
        //    start with 1 and end in 0
        //    start with 1 and end in 1
        // if we have a 0 at all, we have one more valid unique subsequence

        long start1end0 = 0;
        long start1end1 = 0;
        long has0 = 0;

        // we will go from left to right, meaning the current char
        // is our ending
        // as we are adding to prior subseqences, we know they are unique
        // due to the simple fact that they are longer

        for(int i = 0; i < n; ++i) {
            if( binary[i] == '0' ) {
                has0 = 1;
                start1end0 = (start1end0 + start1end1) % MOD;
            } else
                start1end1 = (start1end0 + start1end1 + 1) % MOD;
        }

        return (start1end0 + start1end1 + has0) % MOD;
    }
};
