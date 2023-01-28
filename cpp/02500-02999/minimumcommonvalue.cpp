
// 2540. Minimum Common Value
// https://leetcode.com/problems/minimum-common-value/



class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        // quick check
        if( nums2[0] > nums1[n1-1] || nums1[0] > nums2[n2-1] )
            return -1;


        for(int i = 0, j = 0; i < n1 & j < n2; ) {
            if( nums1[i] < nums2[j] ) {
                ++i;
            } else if( nums2[j] < nums1[i] )
                ++j;
            else
                return nums1[i]; // return nums2[j]
        }

        return -1;
    }
};
