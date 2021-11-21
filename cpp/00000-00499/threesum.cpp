
// 15. 3Sum
// https://leetcode.com/problems/3sum/



class Solution {
private:
    void twoSum(vector<int>& nums, int n, int s, vector<vector<int>>& ans) {

        int target = -nums[s];

        int l = s + 1; // left idx
        int r = n - 1; // right idx
        int sum;
        while(l < r) {
            sum = nums[l] + nums[r];
            if( sum == target ) {
                ans.push_back({nums[s], nums[l], nums[r]});
                ++l; while(l<r && nums[l-1] == nums[l]) ++l;
                --r; while(l<r && nums[r+1] == nums[r]) --r;
            } else if( sum < target ) {
                ++l;
            } else {
                // sum > 0
                --r;
            }
        }
    }

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        size_t n = nums.size();
        if( n <= 2 ) return {};
        if( n == 3 ) {
            if( nums[0]+nums[1]+nums[2] == 0 ) return {nums};
            else return {};
        }

        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i = 0; i < n-2; ++i) {
            if( i > 0 && nums[i-1] == nums[i] ) continue;
            twoSum(nums,n,i,ans);
        }

        return ans;
    }
};
