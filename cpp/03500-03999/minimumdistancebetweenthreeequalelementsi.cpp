
// 3740. Minimum Distance Between Three Equal Elements I
// https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/



class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 100

        int ans = INT_MAX;

        // brute force

        // key: x value: list of indices i where nums[i] == x
        map<int,vector<int>> mp;

        for(int i = 0; i < n; ++i)
            mp[nums[i]].push_back(i);


        for(auto& p: mp) {
            int pos_sz = p.second.size();
            if( pos_sz < 3 )
                continue;
            for(int idx = 0; idx < pos_sz - 2; ++idx) {
                int i = p.second[idx];
                int j = p.second[idx + 1];
                int k = p.second[idx + 2];
                int dist = abs(i - j) + abs(j - k) + abs(k - i);
                ans = min(ans, dist);
            }
        }

        return ans != INT_MAX ? ans : -1;
    }
};
