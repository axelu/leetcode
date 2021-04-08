
// 448. Find All Numbers Disappeared in an Array
// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/





class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<int> ans;
        int expect = 1;
        for(int i = 0; i < n; ++i) {
            while( nums[i] > expect ) {
                ans.push_back(expect);
                ++expect;
            }
            if( nums[i] == expect ) {
                ++expect;
            }
        }
        while( expect <= n ) {
            ans.push_back(expect);
            ++expect;
        }
        return ans;
    }
};
