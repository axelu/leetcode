
// 2943. Maximize Area of Square Hole in Grid
// https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/



class Solution {
private:
    int max_consecutive(vector<int>& nums) {
        // assumes nums is sorted
        int n = nums.size();
        int cmx = 1;
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] + 1 == nums[i] ) {
                ++cnt;
            } else {
                cmx = max(cmx,cnt);
                cnt = 1;
            }
        }
        // finish up
        cmx = max(cmx,cnt);
        return cmx;
    }

public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {

        // max consecutive number of elements

        sort(hBars.begin(),hBars.end());
        int consecutive_horizontal_max = max_consecutive(hBars);

        sort(vBars.begin(),vBars.end());
        int consecutive_vertical_max = max_consecutive(vBars);

        int t = min(consecutive_horizontal_max,consecutive_vertical_max) + 1;

        return t*t;
    }
};
