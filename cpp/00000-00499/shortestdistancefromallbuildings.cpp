
// 317. Shortest Distance from All Buildings
// https://leetcode.com/problems/shortest-distance-from-all-buildings/
// became a problem in the daily challenge September 22 2021
// https://leetcode.com/explore/featured/card/september-leetcoding-challenge-2021/639/week-4-september-22nd-september-28th/3983/

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        
        // 0 marks an empty land that you can pass by freely,
        // 1 marks a building that you cannot pass through, and
        // 2 marks an obstacle that you cannot pass through.
        // build house on empty land
        
        // number buildings in the grid
        // There will be at least one building in the grid.
        int nbrBldgs = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 ) ++nbrBldgs;
        
        
        int ans = INT_MAX;
        bool reachedAll = false;
        
        // direction right,down,left,up
        int dirR[] = {0,1,0,-1};
        int dirC[] = {1,0,-1,0};
        
        queue<pair<pair<int,int>,int>> q;
        int seen[m*n];
        int x,y,x_start,y_start,x_new,y_new,seenIdx,cnt,dist,totalDist,step;
        for(int i = 0; i < m; ++i) {     // row
            for(int j = 0; j < n; ++j) { // col
                if( grid[i][j] == 0 ) {  // empty land
                    
                    // BFS starting at each empty cell
                    x_start = i;
                    y_start = j;
                    totalDist = 0;
                    cnt = 0;
                    memset(seen,0,sizeof seen);
                    q.push({{i,j},0});
                    seenIdx = i*n+j;
                    seen[seenIdx] = 1;
                    while(!q.empty()) {
                        x = q.front().first.first;
                        y = q.front().first.second;
                        step = q.front().second;
                        q.pop();
                        
                        // explore all 4 directions
                        for(int k = 0; k < 4; ++k) {
                            x_new = x+dirR[k];
                            if( x_new < 0 || x_new == m ) continue;
                            y_new = y+dirC[k];
                            if( y_new < 0 || y_new == n ) continue;
                            
                            // obstacle?
                            if( grid[x_new][y_new] == 2 ) continue;
                            
                            // already seen?
                            seenIdx = x_new*n+y_new;
                            if( seen[seenIdx] ) continue;
                            
                            seen[seenIdx] = 1;
                            
                            // building?
                            if( grid[x_new][y_new] == 1 ) {
                                // Manhattan Distance
                                // dist = abs(x_new-x_start) + abs(y_new-y_start);
                                dist = step+1;
                                totalDist += dist;
                                ++cnt;
                                continue;
                            }
                            
                            q.push({{x_new,y_new},step+1});
                        }
                    }
                    
                    if( cnt == nbrBldgs ) {
                        reachedAll = true;
                        ans = min(ans,totalDist);
                    } else {
                        // if we did not reach all houses, then any cell visited 
                        // also cannot reach all houses.
                        // set all cells visted to 2 so we do not check them again
                        for(int k = 0; k < m*n; ++k) {
                            x = k/n;
                            y = k%n;
                            if( seen[k] && grid[x][y] == 0 ) {
                                grid[x][y] = 2;
                            }
                        }
                    }
                }
            }
        }
        return reachedAll ? ans : -1;
    }
};
