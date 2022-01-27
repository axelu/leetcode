
// 2091. Removing Minimum and Maximum From Array
// https://leetcode.com/problems/removing-minimum-and-maximum-from-array/



class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        int mn = INT_MAX, mx = INT_MIN, pmn, pmx;
        for(int i = 0; i < n; ++i) {
            if( nums[i] < mn ) {
                pmn = i;
                mn = nums[i];
            }
            if( nums[i] > mx ) {
                pmx = i;
                mx = nums[i];
            }
        }

        int a = INT_MAX, b = INT_MAX, c = INT_MAX;
        if( pmn < pmx ) {
            a = (pmn + 1) + (n - pmx);  // delete from front and back
            b = (pmx + 1);              // delete from front only
            c = (n - pmn);              // delete from back only
        } else {
            // pmn > pmx, cannot be equal
            a = (pmx + 1) + (n - pmn);  // delete from front and back
            b = (pmn + 1);              // delete from front only
            c = (n - pmx);              // delete from back only
        }


        return min({a,b,c});
    }
};
