
// 1926. Nearest Exit from Entrance in Maze
// https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/



class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();

        int seen[m][n];memset(seen,0,sizeof seen);

        // four directions right,down,left,up
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        // BFS
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[2] > b[2];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        pq.push({entrance[0],entrance[1],0});
        seen[entrance[0]][entrance[1]] = 1;
        int i,i_new,j,j_new,steps;
        while(!pq.empty()) {
            i     = pq.top()[0];
            j     = pq.top()[1];
            steps = pq.top()[2];
            pq.pop();

            for(int k = 0; k < 4; ++k) {
                i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;

                j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                // is the cell a wall?
                if( maze[i_new][j_new] == '+' )
                    continue;

                if( seen[i_new][j_new] )
                    continue;

                if( i_new == 0 || i_new == m-1 ||
                    j_new == 0 || j_new == n-1 )
                    return steps+1;

                seen[i_new][j_new] = 1;
                pq.push({i_new,j_new,steps+1});
            }
        }
        return -1;
    }
};
