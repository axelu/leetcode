
// 1983. Widest Pair of Indices With Equal Range Sum
// https://leetcode.com/problems/widest-pair-of-indices-with-equal-range-sum/




class Solution {
public:
    int widestPairOfIndices(vector<int>& nums1, vector<int>& nums2) {
        // from the hint:
        // if the difference between the two prefix sums at an
        // index i is x, and x again at a different index j,
        // then the sum of nums1 from index i + 1 to index j is equal
        // to the sum of nums2 from index i + 1 to index j

        int n = nums1.size(); // n == nums1.length == nums2.length

        int ans = 0;

        unordered_map<int,int> um; // diff,index
        um[0] = 0;

        int prefixSum1[n+1]; prefixSum1[0] = 0;
        int prefixSum2[n+1]; prefixSum2[0] = 0;
        int d;
        for(int i = 1; i <= n; ++i) {
            prefixSum1[i] = prefixSum1[i-1] + nums1[i-1];
            prefixSum2[i] = prefixSum2[i-1] + nums2[i-1];

            // record the 1st index at which we see a given
            // difference between the two prefix sums
            d = prefixSum1[i] - prefixSum2[i];
            auto p = um.insert({d,i});
            if( !p.second )
                ans = max(ans,i-p.first->second);
        }


        return ans;
    }
};
