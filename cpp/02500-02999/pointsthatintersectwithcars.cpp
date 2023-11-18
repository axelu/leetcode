
// 2848. Points That Intersect With Cars
// https://leetcode.com/problems/points-that-intersect-with-cars/






class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int line[102];memset(line,0,sizeof line);

        for(auto v: nums) {
            ++line[v[0]];
            --line[v[1]+1];
        }

        int ans = 0;

        // line sweep
        int cur = 0;
        for(int i = 0; i <= 100; ++i) {
            cur += line[i];
            if( cur > 0 )
                ++ans;
        }

        return ans;
    }
};
