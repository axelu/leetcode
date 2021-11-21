
// 11. Container with most Water
// https://leetcode.com/problems/container-with-most-water/
// day 17 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3643/


class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();

        int ans = 0;
        int l = 0, r = n-1;
        int lh, rh;
        while( l < r ) {
            lh = height[l];
            rh = height[r];
            ans = max(ans,min(lh,rh) * (r-l));
            if( lh < rh ) {
                while( l < r ) {
                    ++l;
                    if( height[l] > lh ) break;
                }
            } else {
                while( l < r ) {
                    --r;
                    if( height[r] > rh ) break;
                }
            }
        }
        return ans;
    }
};
