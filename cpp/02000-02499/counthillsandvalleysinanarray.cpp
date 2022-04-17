
// 2210. Count Hills and Valleys in an Array
// https://leetcode.com/problems/count-hills-and-valleys-in-an-array/



class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int dir = 0; // 0 unset, -1 desc, 1 asc
        int n = nums.size();
        int ans = 0;
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] < nums[i] ) {
                if( dir == -1 )
                    ++ans;
                dir = 1;
            } else if( nums[i-1] > nums[i] ) {
                if( dir == 1 )
                    ++ans;
                dir = -1;
            }
        }

        return ans;
    }
};
