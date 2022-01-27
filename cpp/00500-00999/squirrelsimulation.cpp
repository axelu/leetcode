
// 573. Squirrel Simulation
// https://leetcode.com/problems/squirrel-simulation/
// day 1 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3624/



class Solution {
public:
    int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {
        int n = nuts.size();    // number of nuts
        int xdiff,ydiff,distNutToTree,distNutToSquirrel;
        int mx = INT_MIN; // max distance we can save
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            // dist of nut to tree
            xdiff = abs(tree[0]-nuts[i][0]);
            ydiff = abs(tree[1]-nuts[i][1]);
            distNutToTree = xdiff+ydiff;
            ans += 2* distNutToTree;
            // dist of nut to squirrel
            xdiff = abs(squirrel[0]-nuts[i][0]);
            ydiff = abs(squirrel[1]-nuts[i][1]);
            distNutToSquirrel = xdiff+ydiff;
            mx = max(mx,distNutToTree-distNutToSquirrel);
        }

        return ans - mx;
    }
};
