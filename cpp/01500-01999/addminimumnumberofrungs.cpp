
// 1936. Add Minimum Number of Rungs
// https://leetcode.com/problems/add-minimum-number-of-rungs/
// https://leetcode.com/contest/weekly-contest-250/problems/add-minimum-number-of-rungs/





class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        int n = rungs.size();

        int ans = 0;

        int currHeight = 0;
        for(int i = 0; i < n; ++i) {
            // can we make it to the next rung?
            if( rungs[i] - currHeight > dist ) {
                // we need to add rungs
                int t = (rungs[i]-currHeight)/dist;
                ans += t;
                if( (rungs[i]-currHeight)%dist == 0 )
                    --ans;
            }
            currHeight = rungs[i];
        }


        return ans;
    }
};
