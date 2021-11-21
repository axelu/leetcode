
// 1877. Minimize Maximum Pair Sum in Array
// https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/



class Solution {
public:
    int minPairSum(vector<int>& nums) {
        int n = nums.size();
        if( n == 2 ) return nums[0]+nums[1];
        
        sort(nums.begin(),nums.end());
        int ans = 0, l = 0, r = n-1;
        while(l<r) {
            ans = max(ans,nums[l]+nums[r]);
            ++l;
            --r;
        }
        
        return ans;
    }
};
