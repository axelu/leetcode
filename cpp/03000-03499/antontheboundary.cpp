
// 3028. Ant on the Boundary
// https://leetcode.com/problems/ant-on-the-boundary/



class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int ans = 0;
        int pos = 0;
        for(int x: nums) {
            pos += x;
            if( pos == 0 )
                ++ans;
        }

        return ans;    }
};
