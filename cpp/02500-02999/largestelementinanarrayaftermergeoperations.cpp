
// 2789. Largest Element in an Array after Merge Operations
// https://leetcode.com/problems/largest-element-in-an-array-after-merge-operations/




class Solution {
public:
    long long maxArrayValue(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];

        long long mx = 0;
        long long nxt = nums[n-1];
        for(int i = n-2; i >= 0; --i) {

            if( nums[i] <= nxt ) {
                nxt = nums[i] + nxt;
            } else {
                nxt = nums[i];
            }
            mx = max(mx,nxt);
        }

        return mx;
    }
};
