
// 2771. Longest Non-decreasing Subarray From Two Arrays
// https://leetcode.com/problems/longest-non-decreasing-subarray-from-two-arrays/





class Solution {
private:
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // nums1.size() == nums2.size()
        if( n == 1 )
            return 1;

        int ans = 1;

        int mem1[n]; // length of non-decreasing subarray starting at nums1[i]
        mem1[n-1] = 1;
        int mem2[n]; // length of non-decreasing subarray starting at nums2[i]
        mem2[n-1] = 1;


        for(int i = n-2; i >= 0; --i) {
            // nums1
            int a = 1, b = 1;
            if( nums1[i+1] >= nums1[i] ) {
                a += mem1[i+1];
            }
            if( nums2[i+1] >= nums1[i] ) {
                b += mem2[i+1];
            }
            mem1[i] = max(a,b);

            // nums2
            int c = 1, d = 1;
            if( nums1[i+1] >= nums2[i] ) {
                c += mem1[i+1];
            }
            if( nums2[i+1] >= nums2[i] ) {
                d += mem2[i+1];
            }
            mem2[i] = max(c,d);

            ans = max({ans,mem1[i],mem2[i]});
        }

        return ans;
    }
};
