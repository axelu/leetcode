
// 3523. Make Array Non-decreasing
// https://leetcode.com/problems/make-array-non-decreasing/




class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        /*
        stack<int> stck; // monotonically non-decreasing stack
        for(int x: nums) {
            if( stck.empty() || x >= stck.top() )
                stck.push(x);
        }
        return stck.size();
        */
        int mx = 0;
        int ans = 0;
        for(int x: nums) {
            if( x >= mx ) {
                ++ans;
                mx = x;
            }
        }
        return ans;
    }
};
