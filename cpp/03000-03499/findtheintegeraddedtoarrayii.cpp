
// 3132. Find the Integer Added to Array II
// https://leetcode.com/problems/find-the-integer-added-to-array-ii/




class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = n1 - 2;

        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());

        for(int x = -1000; x <= 1000; ++x) {
            int i = 0; // index in nums1
            int j = 0; // index in nums2

            while( i < n1 && j < n2 && i - j < 3 ) {
                if( nums1[i] + x == nums2[j] ) {
                    ++i;
                    ++j;
                } else {
                    // "delete" i
                    ++i;
                }
            }
            if( j == n2 )
                return x;
        }

        // because test cases are generated in a way that there is an integer x
        // such that nums1 can become equal to nums2 by removing two elements
        // and adding x to each element of nums1, we should never get here.
        return INT_MAX;
    }
};
