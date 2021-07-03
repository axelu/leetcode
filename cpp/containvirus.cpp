
// 749. Contain Virus
// https://leetcode.com/problems/contain-virus/




class Solution {
private:

    struct T{
        int perimeter;
        vector<vector<int>> area;
        vector<vector<int>> frontier;
        T() : perimeter(0), area({}), frontier({}) {}
    };

    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    void explore(vector<vector<int>>& grid, int m, int n, int i, int j,
                 int seen[], int frontier[], T& t) {
        // cout << "i " << i << " j " << j << endl;

        int seenIdx = i*n+j;
        seen[seenIdx] = 1;
        t.area.push_back({i,j});

        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            // uninfected cell? = frontier
            if( grid[i_new][j_new] == 0 ) {
                // cout << "frontier i_new " << i_new << " j_new " << j_new << endl;
                ++t.perimeter;
                if( !frontier[i_new*n+j_new] ) {
                    frontier[i_new*n+j_new] = 1;
                    t.frontier.push_back({i_new,j_new});
                }
                continue;
            }

            // disinfected cell?
            if( grid[i_new][j_new] == 101 )
                continue;

            // infected cell we have seen before?
            if( seen[i_new*n+j_new] )
                continue;

            explore(grid,m,n,i_new,j_new,seen,frontier,t);
        }
    }

    void disinfect(vector<vector<int>>& grid, const vector<vector<int>>* area) {
        for(int i = 0; i < area->size(); ++i)
            grid[(*area)[i][0]][(*area)[i][1]] = 101;
    }

    void spread(vector<vector<int>>& grid, const vector<vector<int>>* frontier) {
        for(int i = 0; i < frontier->size(); ++i)
            grid[(*frontier)[i][0]][(*frontier)[i][1]] = 1;
    }

public:
    int containVirus(vector<vector<int>>& isInfected) {
        int m = isInfected.size();
        int n = isInfected[0].size();

        int l = m*n;
        int seen[l];
        int frontier[l];

        int ans = 0;

        // sort infected areas by 'most viral' aka largest frontier
        auto cmp = [](const T& a, const T& b){
            return a.frontier.size() < b.frontier.size();
        };
        priority_queue<T,vector<T>,decltype(cmp)> pq(cmp);

        while(true) {
            memset(seen,0,sizeof seen);
            for(int i = 0; i < m; ++i) {
                for(int j = 0; j < n; ++j) {
                    if( isInfected[i][j] == 1 && !seen[i*n+j] ) { // infected cell not seen before
                        // reset frontier
                        memset(frontier,0,sizeof frontier);
                        T t;
                        explore(isInfected,m,n,i,j,seen,frontier,t);
                        // cout << t.perimeter << endl;
                        pq.push(t);
                    }
                }
            }

            if( pq.empty() ) // no infected areas [anymore]
                break;

            // it could also be that there are no frontiers left,
            // meaning the virus spread througout the entire area
            if( pq.top().perimeter == 0 )
                break;

            // disinfect most viral area
            ans += pq.top().perimeter;
            disinfect(isInfected,&pq.top().area);
            pq.pop();

            if( pq.empty() ) // no infected areas [anymore]
                break;

            // spread
            while(!pq.empty()) {
                spread(isInfected,&pq.top().frontier);
                pq.pop();
            }
        }

        return ans;
    }
};
