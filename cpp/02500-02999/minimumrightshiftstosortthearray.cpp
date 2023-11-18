
// 2855. Minimum Right Shifts to Sort the Array
// https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/




class Solution {
public:
    int minimumRightShifts(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int mn = 101;
        int mn_element;
        for(int i = 0; i < n; ++i)
            if( nums[i] < mn ) {
                mn = nums[i];
                mn_element = i;
            }

        // mn elment at mn_element
        int right_shift = mn_element == 0 ? 0 : n - mn_element;
        // cout << "right_shift " << right_shift << endl;
        for(int i = 1; i < n; ++i) {
            int cur =  (mn_element + i)      % n;
            int pre = ((mn_element + i) - 1) % n;
            // cout << "i " << i << " pre " << pre << " cur " << cur << endl;
            if( nums[pre] > nums[cur] )
                return -1;
        }

        return right_shift;
    }
};
