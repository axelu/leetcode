
// 496. Next Greater Element I
// https://leetcode.com/problems/next-greater-element-i/


class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // TODO edge cases
        size_t n1 = nums1.size();
        size_t n2 = nums2.size();

        vector<int> ans(n1);

        // brute force
        int t;
        bool f;
        for(int i = 0; i < n1; ++i) {
            t = -1;
            f = false;
            for( int j = 0; j < n2; ++j) {
                if( nums2[j] == nums1[i] ) {
                    f = true;
                    continue;
                }
                if( f && nums2[j] > nums1[i] ) {
                    t = nums2[j];
                    break;
                }
            }
            ans[i] = t;
        }

        return ans;
    }
};
