
// 1955. Count Number of Special Subsequences
// https://leetcode.com/problems/count-number-of-special-subsequences/
// https://leetcode.com/contest/weekly-contest-252/problems/count-number-of-special-subsequences/





class Solution {
private:
    long MOD = 1000000007;



public:
    int countSpecialSubsequences(vector<int>& nums) {
        int n = nums.size();
        if( n < 3 )
            return 0;
        if( n == 3 )
            return nums[0] == 0 && nums[1] == 1 && nums[2] == 2;


        // solving smaller problem 1st: 1's followed by 2's

        // example
        // 0 1 2 3 4 5 6 7
        // 0 1 2 1 1 1 2 2
        //   |   | | |
        //   |   | | there are 2 2's to the right which gives 2^2 - 1 combinations  3
        //   |   | there are 2 2's to the right which gives 2^2 - 1 combinations +  3
        //   |   | the number of combinations from the 1 to the right               3
        //   |   there are 2 2's to the right which gives 2^2 - 1 combinations +    3
        //   |   plus the number of combinations from the 1st 1 to the right        6
        //   |   plus the number of combinations from the 2nd 1 to the right        3
        //   there are 3 2's to the right, which gives 2^2 - 1 combinations         7
        //   sum of all the options for all 1s to the right                        21
        //                                                                       ----
        //                                                                         49

        // example
        // 0 1 2 3 4 5 6 7
        // 0 1 2 1 1 2 1 2
        //   7   3 3   1     contribution due to two's to the right
        //   8   4 1         contribution due to one's to the right
        //   4   1           -"-
        //   1               -"-
        // ---------------
        //  20   8 4   1   = 33

        unsigned long long numberOfTwos  = 0;
        unsigned long long numberOfOnes  = 0;
        unsigned long long numberOfZeros = 0;

        // going from right to left
        for(int i= n-1; i >= 0; --i) {

            if( nums[i] == 2 ) {
                numberOfTwos = numberOfTwos*2 + 1;
                numberOfTwos = numberOfTwos % MOD;

            } else if (nums[i] == 1) {
                numberOfOnes += numberOfOnes + numberOfTwos;
                numberOfOnes = numberOfOnes % MOD;

            } else {
                // nums[i] == 0
                numberOfZeros += numberOfZeros + numberOfOnes;
                numberOfZeros = numberOfZeros % MOD;
            }
        }

        return numberOfZeros;

    }
};
