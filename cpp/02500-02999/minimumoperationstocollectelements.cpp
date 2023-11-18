
// 2869. Minimum Operations to Collect Elements
// https://leetcode.com/problems/minimum-operations-to-collect-elements/




class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        unordered_set<int> us;
        for(int i = 1; i <= k; ++i)
            us.insert(i);

        int n = nums.size();
        int i = n-1;
        for(; !us.empty() && i >= 0; --i)
            us.erase(nums[i]);

        return n-1-i;
    }
};
