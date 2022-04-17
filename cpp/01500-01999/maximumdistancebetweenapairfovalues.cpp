
// 1855. Maximum Distance Between a Pair of Values
// https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/



class Solution {
private:
    // binary search
    int search(vector<int>& nums1, int s, int e, int target) {
        // nums1 is non-increasing (so it can have duplicates)
        // returns the left most index x in nums1 where
        // nums1[x] <= target

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( nums1[mid] <= target ) {
            // can we do better?
            int t = search(nums1,s,mid-1,target);
            return t != -1 ? t : mid;
        } else {
            return search(nums1,mid+1,e,target);
        }
    }

public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        // idea
        // go into nums1 and find in range [0,min(j,nums1.size()-1)]
        // the leftmost index i where nums1[i] <= nums2[j]

        int n1 = nums1.size();
        int n2 = nums2.size();
        int ans = 0;
        int t = -1;
        int i = 0;
        for(int j = 0; j < n2; ++j) {
            // once we have found an index i in nums1
            // we cannot do better
            t = search(nums1,i,min(j,n1-1),nums2[j]);
            if( t != -1 ) {
                i = t;
                ans = max(ans,j-i);
            }
        }

        return ans;
    }
};
