
// 499. The Maze III
// https://leetcode.com/problems/the-maze-iii/





class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        int m = maze.size();
        int n = maze[0].size();

        // directions
        int  dirR[4] = { 0,  1,  0, -1 };
        int  dirC[4] = { 1,  0, -1,  0 };
        int  dirM[4] = { 0,  1,  2,  3 };
        char dirA[4] = {'r','d','l','u'};
        //               r   d   l   u   direction in which we are leaving a given cell

        struct T{
            int i;
            int j;
            int k;
            int step;
            string instructions;
        };

        // BFS
        int seen[m*n][4];memset(seen,0,sizeof seen);
        queue<T> q;

        // getting started
        int i = ball[0];
        int j = ball[1];
        int i_new,j_new,k;
        string instructions;
        for(k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new >= m )
                continue;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new >= n )
                continue;

            // obstacle?
            if( maze[i_new][j_new] == 1 )
                continue;

            seen[i*n+j][k] = 1;
            instructions = "";
            instructions += dirA[k];
            q.push({i_new,j_new,k,1,instructions});
        }

        auto cmp = [](const T& a, const T& b) {
            return a.instructions > b.instructions;
        };
        priority_queue<T,vector<T>,decltype(cmp)> pq(cmp);

        vector<string> ans;
        int shortestDist = -1;
        int step;
        bool didStop;
        T t;
        while(!q.empty()) {
            t = q.front();
            q.pop();

            // cout << "in  " << t.step << " i " << t.i << " j " << t.j << " k " << t.k << " " << t.instructions << endl;

            // did we arrive at the hole?
            if( t.i == hole[0] && t.j == hole[1] ) {
                shortestDist = t.step;
                ans.push_back(t.instructions);
                continue;
            }

            didStop = false;

            i_new = t.i+dirR[t.k];
            if( i_new < 0 || i_new >= m )
                didStop = true;

            j_new = t.j+dirC[t.k];
            if( j_new < 0 || j_new >= n )
                didStop = true;

            // obstacle?
            if( !didStop )
                if( maze[i_new][j_new] == 1 )
                    didStop = true;

            if( didStop ) {
                // cout << "stopped" << endl;

                // choose a new direction
                for(int p = 0; p < 4; ++p) {
                    if( p == t.k ) continue; // skip the direction we were travling in

                    i_new = t.i+dirR[p];
                    if( i_new < 0 || i_new >= m )
                        continue;

                    j_new = t.j+dirC[p];
                    if( j_new < 0 || j_new >= n )
                        continue;

                    // obstacle
                    if( maze[i_new][j_new] == 1 )
                        continue;

                    // if another version already arrived at the hole,
                    // would our path be able compete?
                    if( shortestDist != -1 && t.step+1 > shortestDist )
                        continue;

                    pq.push({i_new,j_new,p,t.step+1,t.instructions+dirA[p]});
                }

            } else {
                // keep going

                // if another version already arrived at the hole,
                // would our path be able compete?
                if( shortestDist != -1 && t.step+1 > shortestDist )
                    continue;

                pq.push({i_new,j_new,t.k,t.step+1,t.instructions});
            }

            // collect all new exits for a given step and only continue
            // the once with the lexicographically minimum instruction
            // when exiting the same cell in the same direction
            if(q.empty()) {
                // if we found the hole in the meantime
                // there is no need to go forward
                if( shortestDist != -1 )
                    break;

                while(!pq.empty()) {
                    t = pq.top();
                    pq.pop();

                    // cout << "out " << t.step << " i " << t.i << " j " << t.j << " k " << t.k << " " << t.instructions << endl;

                    if( seen[t.i*n+t.j][t.k] )
                        continue;
                    seen[t.i*n+t.j][t.k] = 1;
                    q.push(t);
                }
            }
        }

        if( ans.empty() ) return "impossible";
        sort(ans.begin(),ans.end()); // return lexicographically minimum instruction
        // for(string s : ans) cout << s << endl;
        return ans[0];
    }
};
