
// 2239. Find Closest Number to Zero
// https://leetcode.com/problems/find-closest-number-to-zero/



class Solution {
public:
    int findClosestNumber(vector<int>& nums) {
        int ans = -100000;
        int d = 100000;
        for(int x: nums)
            if( abs(0-x) == d ) {
                if( x > ans )
                    ans = x;
            } else if( abs(0-x) < d ) {
                ans = x;
                d = abs(0-x);
            }

        return ans;
    }
};
