
// 2481. Minimum Cuts to Divide a Circle
// https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/



class Solution {
public:
    int numberOfCuts(int n) {
        // edge case
        if( n == 1 )
            return 0;

        return n % 2 == 0 ? n/2 : n;
    }
};
