
// 798. Smallest Rotation with Highest Score
// https://leetcode.com/problems/smallest-rotation-with-highest-score/




class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = nums.size();

        int points[n+1];memset(points,0,sizeof points);

        for(int i = 0; i < n; ++i) {
            int l=0,h=0;
            if( nums[i] <= i ) {
                // we score w/o doing any shift up doing i-nums[i] shifts to the left
                ++points[0];
                --points[i-nums[i]+1];
                // additionally we score if nums[i] occupies indicies i+1 to n-1 after rotations
                // those would be i+1 to n-1 roations
                ++points[i+1];
                --points[n];

            } else {
                // we score if nums[i] occupies indicies nums[i] to n-1 after rotations
                ++points[i+1];
                --points[(i+1)+((n-1)-nums[i]) + 1];
            }
        }

        // line sweep of points
        int score = 0; // running score
        int mx = -1;
        int k;
        for(int i = 0; i < n; ++i) {
            score += points[i];
            if( score > mx ) {
                k = i;
                mx = score;
            }
        }

        return k;
    }
};
