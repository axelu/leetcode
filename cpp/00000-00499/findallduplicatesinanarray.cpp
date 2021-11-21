
// 442. Find All Duplicates in an Array
// https://leetcode.com/problems/find-all-duplicates-in-an-array/



class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        if( n == 1 ) return ans;

        int cnt[n+1];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i) {
            ++cnt[nums[i]];
            if( cnt[nums[i]] == 2 ) ans.push_back(nums[i]);
        }

        return ans;
    }
};
