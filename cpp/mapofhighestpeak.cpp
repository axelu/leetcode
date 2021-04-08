
// 1765. Map of Highest Peak
// https://leetcode.com/problems/map-of-highest-peak/




class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size();     // rows
        int n = isWater[0].size();  // cols


        // BFS starting simultaneously
        // flip: org: land =  0, water = 1
        //       new: land = -1, water = 0
        queue<pair<pair<int,int>,int>> q; // cell[i][j],source level
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( isWater[i][j] == 1 ) {
                    isWater[i][j] = 0;
                    q.push({{i,j},0});
                } else {
                    isWater[i][j] = -1;
                }

        // direction right,down,left,up
        int dirR[] = {0,1,0,-1};
        int dirC[] = {1,0,-1,0};

        int seen[m*n]; memset(seen,0,sizeof seen);
        int x,y,x_new,y_new,h,seenIdx;
        while(!q.empty()) {
            x = q.front().first.first;
            y = q.front().first.second;
            h = q.front().second;
            q.pop();

            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {
                x_new = x + dirR[k];
                if( x_new < 0 || x_new == m ) continue;

                y_new = y + dirC[k];
                if( y_new < 0 || y_new == n ) continue;

                // is water?
                if( isWater[x_new][y_new] == 0 ) continue;

                // already seen?
                seenIdx = x_new*n+y_new;
                if( seen[seenIdx] ) continue;

                isWater[x_new][y_new] = h+1;
                seen[seenIdx] = 1;
                q.push({{x_new,y_new},h+1});
            }
        }
        return isWater;
    }
};
