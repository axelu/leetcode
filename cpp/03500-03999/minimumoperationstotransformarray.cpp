
// 3724. Minimum Operations to Transform Array
// https://leetcode.com/problems/minimum-operations-to-transform-array/


class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();

        long long ans = 1LL; // append will always consume 1 operation
        long long d = LLONG_MAX;

        int nums2_n = nums2[n];
        for(int i = 0; i < n; ++i) {
            if( d > 0LL ) {
                if( (nums1[i] >= nums2_n && nums2[i] <= nums2_n) ||
                    (nums1[i] <= nums2_n && nums2[i] >= nums2_n) ) {
                    // one is greater or equal and the other is less or equal
                    // or vice versa, so while we are
                    // incrementing or decrementing nums1[i] to make
                    // nums1[i] == nums2[i], we cross nums2_n
                    // at the moment we do our append step
                    d = 0LL;

                } else {
                    // both nums1[i] and nums2[i] are either
                    // greater or smaller than nums2_n
                    // so we use the smallest difference
                    d = min(d, (long long)(abs(nums1[i] - nums2_n)));
                    d = min(d, (long long)(abs(nums2[i] - nums2_n)));
                }
            }
            ans += (long long)(abs(nums1[i]-nums2[i]));
        }

        return ans + d;
    }
};
