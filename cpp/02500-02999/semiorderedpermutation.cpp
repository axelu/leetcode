
// 2717. Semi-Ordered Permutation
// https://leetcode.com/problems/semi-ordered-permutation/




class Solution {
public:
    int semiOrderedPermutation(vector<int>& nums) {
        int n = nums.size();

        int idx1 = -1;
        int idxn = -1;

        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 )
                idx1 = i;
            if( nums[i] == n )
                idxn = i;
        }

        int ans = idx1;
        ans += idxn < idx1 ? (n-1) - idxn - 1 : (n-1) - idxn;

        return ans;
    }
};
