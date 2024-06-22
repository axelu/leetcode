
// 3173. Bitwise OR of Adjacent Elements
// https://leetcode.com/problems/bitwise-or-of-adjacent-elements/




class Solution {
public:
    vector<int> orArray(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 100

        vector<int> ans(n-1);

        for(int i = 0; i < n-1; ++i)
            ans[i] = nums[i] | nums[i+1];

        return ans;
    }
};
