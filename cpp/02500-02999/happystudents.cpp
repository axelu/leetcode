
// 2860. Happy Students
// https://leetcode.com/problems/happy-students/





class Solution {
public:
    int countWays(vector<int>& nums) {
        int n = nums.size();

        // 0 <= nums[i] < nums.length
        // The ith student will become happy if one of these two conditions is met:
        //     The student is selected and the total number of selected students is strictly greater than nums[i].
        //     The student is not selected and the total number of selected students is strictly less than nums[i].
        // observation (from the hints)
        //     if student with nums[i] = x is selected, all the students with nums[j] <= x must be selected
        //     if student with nums[i] = x is not selected, all the students with nums[j] >= x must not be selected

        int ans = 0;

        sort(nums.begin(),nums.end());
        if( nums[0] > 0 ) {
            // not selecting any student is a valid option
            ++ans;
        }

        for(int i = 0; i < n; ++i) {
            if( i+1 < n && nums[i+1] == nums[i] )
                continue;

            // students idx[0,i] inclusive selected
            // students idx[i+1,n-1] inclusive not selected

            int selected = i+1;
            // int notselected = (n-1) - (i+1) + 1;
            // cout << "i " << i << " selected " << selected << " notselected " << notselected << endl;

            if( i < n-1 ) {
                if( selected > nums[i] && selected < nums[i+1] ) {
                    // cout << "condition met" << endl;
                    ++ans;
                }
            } else {
                if( selected > nums[i] ) {
                    // cout << "condition met" << endl;
                    ++ans;
                }
            }
        }

        return ans;
    }
};
