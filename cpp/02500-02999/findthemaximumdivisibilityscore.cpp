
// 2644. Find the Maximum Divisibility Score
// https://leetcode.com/problems/find-the-maximum-divisibility-score/




class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {

        sort(divisors.begin(),divisors.end());

        int score = 0;
        int ans = divisors[0];

        // brute force
        for(int divisor: divisors) {
            int t = 0;
            for(int a: nums)
                if( a % divisor == 0 )
                    ++t;

            if( t > score ) {
                score = t;
                ans = divisor;
            }
        }

        return ans;
    }
};
