
// 1956. Minimum Time For K Virus Variants to Spread
// https://leetcode.com/problems/minimum-time-for-k-virus-variants-to-spread/




class Solution {
private:
    int cnt[101][101];
    int x_mn,x_mx,y_mn,y_mx;
    int n;

    int init(vector<vector<int>>& points, int k) {
        x_mn = 100;
        x_mx = 1;
        y_mn = 100;
        y_mx = 1;
        memset(cnt,0,sizeof cnt);
        n = points.size();

        for(auto& v: points) {
            x_mn = min(x_mn,v[0]);
            x_mx = max(x_mx,v[0]);
            y_mn = min(y_mn,v[1]);
            y_mx = max(y_mx,v[1]);
            if( ++cnt[v[0]][v[1]] >= k )
                return 1;
        }
        return 0;
    }

    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    int solve(vector<vector<int>>& points, int k) {
        // returns the min number of steps <= d at
        // which there is a cell with >= k viruses

        int o[101][101];memset(o,0,sizeof o);

        queue<array<int,4>> q;
        int added[101][101];memset(added,0,sizeof added);
        int seen[101][101][n];memset(seen,0,sizeof seen);
        for(int i = 0; i < n; ++i) {
            if( added[points[i][0]][points[i][1]] )
                continue;
            added[points[i][0]][points[i][1]] = 1;
            q.push({points[i][0],points[i][1],i,cnt[points[i][0]][points[i][1]]});
            seen[points[i][0]][points[i][1]][i] = 1;
        }

        int steps = 0;
        while( !q.empty() ) {

            queue<array<int,4>> q_new;
            while( !q.empty() ) {
                auto[x,y,id,add] = q.front();
                q.pop();

                o[x][y] += add;
                if( o[x][y] >= k )
                    return steps;

                for(int k = 0; k < 4; ++k) {
                    int x_new = x + dirR[k];
                    if( x_new < x_mn || x_new > x_mx)
                        continue;
                    int y_new = y + dirC[k];
                    if( y_new < y_mn || y_new > y_mx)
                        continue;

                    if( seen[x_new][y_new][id] )
                        continue;

                    seen[x_new][y_new][id] = 1;
                    q_new.push({x_new,y_new,id,add});
                }
            }
            q = q_new;
            ++steps;
        }
        return -1;
    }

public:
    int minDayskVariants(vector<vector<int>>& points, int k) {
        if( init(points,k) )
            return 0;

        return solve(points,k);
    }
};
