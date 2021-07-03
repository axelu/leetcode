// 789. Escape The Ghosts
// https://leetcode.com/problems/escape-the-ghosts/


class Solution {
private:
    int md(vector<int>& p1, vector<int>& p2) {
        // manhattan distance |xi - xj| + |yi - yj|
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }

public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        // if there is any ghost at the same distance or closer,
        // then we cannot win

        vector<int> start = {0,0};
        int us = md(start,target);

        for(int i = 0; i < ghosts.size(); ++i) {
            int ghost = md(ghosts[i],target);
            if( ghost <= us )
                return false;
        }

        return true;
    }
};
