
// 2541. Minimum Operations to Make Array Equal II
// https://leetcode.com/problems/minimum-operations-to-make-array-equal-ii/



class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(); // nums1.size() == nums.size()

        if( k == 0 ) {
            for(int i = 0; i < n; ++i)
                if( nums1[i] != nums2[i] )
                    return -1LL;
            return 0LL;
        }

        long long up = 0;
        long long down = 0;

        for(int i = 0; i < n; ++i) {
            if( nums1[i] < nums2[i] ) {
                long long d = nums2[i] - nums1[i];
                if( d % k != 0 )
                    return -1LL;

                long long f = d / k;
                up += f;

            } else if( nums1[i] > nums2[i] ) {
                long long d = nums1[i] - nums2[i];
                if( d % k != 0 )
                    return -1LL;

                long long f = d / k;
                down += f;
            }
        }
        if( up != down )
            return -1LL;

        return up;
    }
};
