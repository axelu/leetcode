
// 2101. Detonate the Maximum Bombs
// https://leetcode.com/problems/detonate-the-maximum-bombs/



class Solution {
private:
    int dfs(vector<int> g[], int u, int seen[]) {
        if( seen[u] )
            return 0;

        seen[u] = 1;
        int ret = 1;

        for(auto& v : g[u] )
            ret += dfs(g,v,seen);

        return ret;
    }

public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        // lets build a graph with all the bombs
        // bombs are connected if their area overlap, so we create an edge
        // then the answer is the connected component with the max number of nodes

        // 1 <= bombs.length <= 100 <- small enough constraint to do O(n^2)
        int n = bombs.size();
        if( n == 1 )
            return 1;

        vector<int> g[n]; // directed graph

        for(int i = 0; i < n-1; ++i) {
            long x1 = bombs[i][0];
            long y1 = bombs[i][1];
            long r1 = bombs[i][2];
            for(int j = i+1; j < n; ++j) {
                long x2 = bombs[j][0];
                long y2 = bombs[j][1];
                long r2 = bombs[j][2];
                // if bomb i and bomb j overlap,
                // then create an edge
                // d   = sqrt( (x2-x1)^2 + (y2-y1)^2 )
                // d^2 =       (x2-x1)^2 + (y2-y1)^2
                // we need to consider which bomb detonates to see if there is an edge
                // aka it is directional
                long d2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
                // can detonation of bomb i reach bomb j?
                if( r1*r1 >= d2 ) {
                    /*
                    cout << "creating directed edge between i " << i << " and j " << j << endl;
                    cout << "i x1 " << x1 << " y1 " << y1 << " r1 " << r1 << endl;
                    cout << "j x2 " << x2 << " y2 " << y2 << " r2 " << r2 << endl;
                    cout << "r1^2 " << r1*r1 << " d2 " << d2 << endl;
                    */
                    g[i].push_back(j);
                }
                if( r2*r2 >= d2 ) {
                    /*
                    cout << "creating edge between j " << j << " and i " << i << endl;
                    cout << "j x2 " << x2 << " y2 " << y2 << " r2 " << r2 << endl;
                    cout << "i x1 " << x1 << " y1 " << y1 << " r1 " << r1 << endl;
                    cout << "r2^2 " << r2*r2 << " d2 " << d2 << endl;
                    */
                    g[j].push_back(i);
                }
            }
        }

        int ans = 1; // we can at least detonate one bomb

        int seen[n];memset(seen,0,sizeof seen);
        for(int i = 0; i < n; ++i) {
            memset(seen,0,sizeof seen);
            ans = max(ans,dfs(g,i,seen));
        }

        return ans;
    }
};
