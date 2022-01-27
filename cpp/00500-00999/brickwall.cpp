
// 554. Brick Wall
// https://leetcode.com/problems/brick-wall/
// day 22 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/596/week-4-april-22nd-april-28th/3717/



class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int m = wall.size();
        int i,j,pos;

        unordered_map<int,int> um; // pos in wall, number of bricks meeting at pos
        pair<unordered_map<int,int>::iterator,bool> p;
        int mx = 0; // number of bricks meeting at pos

        for(i = 0; i < m; ++i) {
            pos = 0;
            for(j = 0; j < wall[i].size()-1; ++j) {
                pos += wall[i][j];
                p = um.insert({pos,1});
                if( !p.second )
                    ++p.first->second;
                mx = max(mx,p.first->second);
            }
        }

        return m-mx;
    }
};
