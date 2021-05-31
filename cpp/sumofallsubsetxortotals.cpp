
// 1863. Sum of All Subset XOR Totals
// https://leetcode.com/problems/sum-of-all-subset-xor-totals/





class Solution {
private:
    void subsetXORSum(vector<int>& nums, int& n, int& ans, int subsetXOR, int idx) {
        // at every step we can either include the element or
        // we can ignore respectively skip the element

        ans += subsetXOR;

        for(int i = idx; i < n; ++i) {
            // include the nums[i] in subset
            subsetXOR ^= nums[i];

            subsetXORSum(nums,n,ans,subsetXOR,i+1);

            // backtracking
            subsetXOR ^= nums[i];
        }
    }
public:
    int subsetXORSum(vector<int>& nums) {
        // 1 <= nums.length <= 12
        int n = nums.size();
        if( n == 1 ) return nums[0];

        int ans = 0;
        subsetXORSum(nums,n,ans,0,0);

        return ans;
    }
};
