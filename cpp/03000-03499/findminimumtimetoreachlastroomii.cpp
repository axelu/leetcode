
// 3342. Find Minimum Time to Reach Last Room II
// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/





class Solution {
private:
    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};


public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int m = moveTime.size();    // rows; 2 <= m == moveTime.length <= 50
        int n = moveTime[0].size(); // cols; 2 <= n == moveTime[i].length <= 50
        // 0 <= moveTime[i][j] <= 1e9


        // Dijkstra

        // min heap
        // time, step, index
        priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;

        // distances
        int A[m*n];
        for(int i = 0; i < m*n; ++i) A[i] = 1100000000;

        // push our source vertex into priority queue
        int s = 0; // we are starting at 0,0 at time t = 0
        pq.push({0,0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int t,step,u,v,weight;
        while(!pq.empty()) {

            t = pq.top()[0];
            step = pq.top()[1];
            u = pq.top()[2];
            pq.pop();

            int i = u / n;
            int j = u % n;

            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;
                int j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                int v = i_new * n + j_new; // u_new

                // we cannot step unto v before moveTime[i_new][j_new]
                int t_new;
                if( step % 2 == 0 )
                    t_new = max(t+1, moveTime[i_new][j_new]+1);
                else
                    t_new = max(t+2, moveTime[i_new][j_new]+2);

                // have we been here earlier?
                if( t_new < A[v] ) {
                    A[v] = t_new;
                    pq.push({t_new,step+1,v});
                }
            }

        }

        return A[m*n-1];
    }
};
