
// 2501. Longest Square Streak in an Array
// https://leetcode.com/problems/longest-square-streak-in-an-array/



class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        int n = nums.size();

        int ans = -1;

        unordered_map<long,int> x2;
        sort(nums.begin(),nums.end());
        for(int i = 0; i < n; ++i) {
            long x = nums[i];
            auto f = x2.find(x);
            int t = f != x2.end() ? f->second : 1;
            if( t > 1 )
                ans = max(ans,t);

            x2[x*x] = t + 1;
        }

        return ans;
    }
};
