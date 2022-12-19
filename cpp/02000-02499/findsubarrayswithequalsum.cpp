
// 2395. Find Subarrays With Equal Sum
// https://leetcode.com/problems/find-subarrays-with-equal-sum/


class Solution {
public:
    bool findSubarrays(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,int> um; // record the 1st occurence of subarray sum

        for(int i = 0; i < n-1; ++i)
            if( !um.insert({nums[i]+nums[i+1],i}).second )
                return true;

        return false;
    }
};
