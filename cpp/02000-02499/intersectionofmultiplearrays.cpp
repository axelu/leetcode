
// 2248. Intersection of Multiple Arrays
// https://leetcode.com/problems/intersection-of-multiple-arrays/



class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        int cnt[1001];memset(cnt,0,sizeof cnt);
        int n = nums.size();
        for(int i = 0; i < n; ++i)
            for(int x: nums[i])
                ++cnt[x];

        vector<int> ans;
        for(int i = 1; i < 1001; ++i)
            if( cnt[i] == n )
                ans.push_back(i);

        return ans;
    }
};
