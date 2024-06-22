
// 3131. Find the Integer Added to Array I
// https://leetcode.com/problems/find-the-integer-added-to-array-i/



class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {
        // int n = nums1.size(); // nums1.size() == nums2.size()

        // it is guaranteed that there is an integer x such that
        // nums1 can become equal to nums2 by adding x to each element of nums1

        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());

        return nums2[0] - nums1[0];
    }
};
