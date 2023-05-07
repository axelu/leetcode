
// 2605. Form Smallest Number From Two Digit Arrays
// https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/



class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) {

        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());

        int i = 0, n1 = nums1.size();
        int j = 0, n2 = nums2.size();

        while( i < n1 && j < n2 ) {
            if( nums1[i] < nums2[j] )
                ++i;
            else if( nums1[i] > nums2[j] )
                ++j;
            else
                return nums1[i];
        }

        return nums1[0] < nums2[0] ? nums1[0] * 10 + nums2[0] : nums2[0] * 10 + nums1[0];
    }
};
