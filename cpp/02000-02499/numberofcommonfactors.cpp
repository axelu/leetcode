
// 2427. Number of Common Factors
// https://leetcode.com/problems/number-of-common-factors/



class Solution {
public:
    int commonFactors(int a, int b) {
        int n = min(a,b);
        int cnt = 1;
        for(int i = 2; i <= n; ++i)
            if( a % i == 0 && b % i == 0 )
                ++cnt;

        return cnt;
    }
};
