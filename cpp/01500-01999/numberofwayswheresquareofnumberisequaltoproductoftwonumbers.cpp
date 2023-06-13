
// 1577. Number of Ways Where Square of Number Is Equal to Product of Two Numbers
// https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/





class Solution {
private:
    int solve(vector<int>& nums1, vector<int>& nums2) {
        int ret = 0;

        // brute force
        unordered_map<long,int> um; // nums[i]^2

        for(long x: nums1)
            ++um[x*x];

        for(int i = 0; i < nums2.size()-1; ++i) {
            for(int j = i+1; j < nums2.size(); ++j) {
                long k = (long)nums2[i] * nums2[j];
                auto f = um.find(k);
                if( f != um.end() )
                    ret += f->second;
            }
        }

        return ret;
    }

public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0;

        ans += solve(nums1,nums2);
        ans += solve(nums2,nums1);

        return ans;
    }
};
