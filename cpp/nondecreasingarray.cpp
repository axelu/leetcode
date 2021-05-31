
// 665. Non-decreasing Array
// https://leetcode.com/problems/non-decreasing-array/
// day 4 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3731/





class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return true;

        bool f = false;
        int prev = nums[0];
        for(int i = 1; i < n; ++i) {
            if( prev > nums[i] ) {
                // cout << "i " << i << " nums[i] " << nums[i] << endl;
                if( f ) return false; // we already had to make one adjustment
                f = true;

                // two options:
                //    a) lower    nums[i-1] OR
                //    b) increase nums[i]

                if( i-1 == 0 || nums[i-2] <= nums[i] ) {
                    // lower nums[i-1]
                    prev = nums[i];
                    continue;
                } else {
                    // increase nums[i]
                    prev = nums[i-1];
                    continue;
                }
            }
            prev = nums[i];
        }

        return true;
    }
};
