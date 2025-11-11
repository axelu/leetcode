
// 3682. Minimum INdex Sum of Common Elements
// https://leetcode.com/problems/minimum-index-sum-of-common-elements/



class Solution {
public:
    int minimumSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // 1 <= nums1.length == nums2.length <= 1e5

        int nums2_idx[200002]; // smallest index of value
        memset(nums2_idx, -1, sizeof nums2_idx);

        int offset = 100000; // -1e5 <= nums1[i], nums2[i] <= 1e5
        for(int i = 0; i < n; ++i) {
            int x = nums2[i];
            if( nums2_idx[x+offset] == -1 ) {
                nums2_idx[x+offset] = i;
            }
        }

        int ans = INT_MAX;

        for(int i = 0; i < n; ++i) {
            int x = nums1[i];
            if( nums2_idx[x+offset] != -1 ) {
                ans = min(ans, i + nums2_idx[x+offset]);
            }
        }

        return ans != INT_MAX ? ans : -1;
    }
};
