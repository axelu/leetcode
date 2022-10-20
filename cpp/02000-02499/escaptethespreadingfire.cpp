
// 2258. Escape the Spreading Fire
// https://leetcode.com/problems/escape-the-spreading-fire/


/*

Case 1
[[0,2,1],[1,1,1],[0,0,0]]
Case 2
[[0,2,1],[0,2,0],[0,2,0]]
Case 3
[[0,0,1],[2,2,2],[0,0,0]]
Case 4
[[0,2,1],[0,2,2],[0,0,0]]
Case 5
[[0,0,1],[2,2,0],[2,2,0]]


Case 8 same time
[[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,2,2,2,0],[0,0,0,0,0]]
Case 8 faster
[[0,2,0,1,1],[0,2,0,2,2],[0,2,0,0,0],[0,2,2,2,0],[0,0,0,0,0]]

[[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
[[0,0,0,0],[0,1,2,0],[0,2,0,0]]
[[0,0,0],[2,2,0],[1,2,0]]
[[0,2,1],[1,1,1],[0,0,0]]
[[0,2,1],[0,2,0],[0,2,0]]
[[0,0,1],[2,2,2],[0,0,0]]
[[0,2,1],[0,2,2],[0,0,0]]
[[0,0,1],[2,2,0],[2,2,0]]
[[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,2,2,2,0],[0,0,0,0,0]]
[[0,2,0,1,1],[0,2,0,2,2],[0,2,0,0,0],[0,2,2,2,0],[0,0,0,0,0]]
[[0,0,0,0,0],[0,2,0,2,0],[0,2,0,2,0],[0,2,1,2,0],[0,2,2,2,0],[0,0,0,0,0]]

*/




class Solution {
private:
    int m,n,g_sz,sh;
    vector<vector<int>> g;
    vector<int> initial_fires;
    vector<int> burning_forest;

    void init(vector<vector<int>>& grid) {
        // populates the graph and the initial fire spots
        // initial fire spots only have outbound edges

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                int u = i*n+j;
                if( grid[i][j] < 2 ) {  // grass or fire
                    for(int k = 0; k < 4; ++k) {
                        int i_new = i + dirR[k];
                        if( i_new < 0 || i_new == m )
                            continue;

                        int j_new = j + dirC[k];
                        if( j_new < 0 || j_new == n )
                            continue;

                        if( grid[i_new][j_new] > 0 ) // fire or wall
                            continue;

                        int v = i_new*n+j_new;
                        g[u].push_back(v);
                    }
                }
                if( grid[i][j] == 1 ) {  // fire
                    initial_fires.push_back(u);
                }
            }

        return;
    }

    int start2safehouse() {
        // assumes no spread of initial fire
        // returns the fastest time from start to safehouse
        // returns 0 if the safehouse cannot be reached from start

        int seen[g_sz];memset(seen,0,sizeof seen);
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        pq.push({0,0});
        seen[0] = 1;
        while( !pq.empty() ) {
            auto[time,u] = pq.top();
            pq.pop();

            if( u == sh ) // reached the safe house
                return time;

            for(int v: g[u]) {
                if( seen[v] )
                    continue;
                seen[v] = 1;
                pq.push({time+1,v});
            }
        }

        return 0;
    }

    pair<int,int> fire(vector<vector<int>>& grid) {

        // each cell with a fire is a starting point
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        int t1 = 0; // time it takes for the fire to reach the safe house
        int t2 = 0; // time it takes for the fire to reach the start [0,0]

        for(int u: initial_fires)
            pq.push({0,u});

        while( !pq.empty() ) {
            auto[time,u] = pq.top();
            pq.pop();

            //cout << "u " << u << " time " << time << endl;

            if( u == sh && t1 == 0 ) // fire reached the safe house
                t1 = time;
            if( u == 0 && t2 == 0 ) // fire reached the start
                t2 = time;

            for(int v: g[u]) {
                //cout << "    v " << v << endl;
                if( burning_forest[v] )
                    continue;
                burning_forest[v] = time+1;
                pq.push({time+1,v});
            }
        }

        // cout << "time for fire to reach safe house " << t1 << endl;
        // cout << "time for fire to reach start      " << t2 << endl;
        return {t1,t2};
    }

    bool can_person_reach_safehouse(int delay) {
        // cout << "can_person_reach_safehouse delay " << delay << endl;
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        // person starts from 0 at time delay
        pq.push({delay,0});
        int seen[g_sz];memset(seen,0,sizeof seen);
        seen[0] = 1;

        while( !pq.empty() ) {
            auto[time,u] = pq.top();
            pq.pop();
            // cout << "u " << u << " time " << time << endl;
            ++time;
            for(int v: g[u]) {
                if( v == sh && burning_forest[v] >= time )
                    return true;

                if( !seen[v] && burning_forest[v] > time ) {
                    seen[v] = 1;
                    pq.push({time,v});
                }
            }
        }

        return false;
    }

    // binary search
    int search(int s, int e) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = can_person_reach_safehouse(mid);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e);
            return t != -1 ? t : mid;
        } else {
            return search(s,mid-1);
        }
    }

public:
    int maximumMinutes(vector<vector<int>>& grid) {
        m    = grid.size();     // rows
        n    = grid[0].size();  // cols
        g_sz = m*n;
        sh   = g_sz-1;          // safe house

        //   fire                            | start        | result
        //   can reach sh | can reach start  | can reach sh |
        // 1      -               -               -           impossible    ->  -1
        // 2      x               -               -           impossible    ->  -1
        // 3      -               x               -           impossible    ->  -1
        // 4      -               -               x           wait forever  -> 1e9
        // 5      x               x               -           we are doomed ->  -1
        // 6      -               x               x           theoretical case only
        // 7      x               -               x           theoretical case only
        // 8      x               x               x           can the person make it?
        // case 8:
        //  if the fire reaches the safe house faster ->  -1

        g.resize(g_sz);
        init(grid);

        int t = start2safehouse();
        if( !t )  // safehouse not reachable from start even w/o fire spreading
            return -1;

        burning_forest.resize(g_sz); // records when the fire is at a given cell
        auto p = fire(grid);
        if( !p.first )           // fire cannot reach the safehouse
            return 1000000000;

        if( p.first < t ) // fire makes it to safehouse before the person
            return -1;

        return search(0,p.second-1);
    }
};
