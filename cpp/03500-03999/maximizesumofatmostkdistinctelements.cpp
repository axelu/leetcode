
// 3684. Maximize Sum of At Most K Distinct Elements
// https://leetcode.com/problems/maximize-sum-of-at-most-k-distinct-elements/



class Solution {
public:
    vector<int> maxKDistinct(vector<int>& nums, int k) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        vector<int> ans;
        int pre = INT_MAX;
        for(int i = n-1; i >= 0; --i) {
            if( nums[i] != pre ) {
                ans.push_back(nums[i]);
                if( ans.size() == k )
                    break;
                pre = nums[i];
            }
        }

        return ans;
    }
};
