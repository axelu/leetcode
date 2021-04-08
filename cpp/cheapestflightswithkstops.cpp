
// 787. Cheapest Flights Within K Stops
// https://leetcode.com/problems/cheapest-flights-within-k-stops/



class Solution {
private:
    vector<int> mem[100];
    bool reachedDst;

    int dfs(int u, vector<vector<int>> g[], int stop, int K, int dst) {
        if( u == dst ) {
            reachedDst = true;
            return 0;
        }
        if( stop > K ) return -1;
        if( mem[u][stop] != -1 ) return mem[u][stop];

        bool reachedDst = false;
        int ans = INT_MAX;
        int v,w,res;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i][0];
            if( v == u ) continue; // skip where we came from
            w = g[u][i][1];
            res = dfs(v,g,stop+1,K,dst);
            if( res >= 0 ) {
                reachedDst = true;
                ans = min(ans,res+w);
            }
        }
        return mem[u][stop] = reachedDst ? ans : -2;
    }
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        if( src == dst ) return 0;

        // directed weighted graph
        vector<vector<int>> g[n];
        int u,v,w; // u = src, v = dst, w = price
        for(int i = 0; i < flights.size(); ++i) {
            u = flights[i][0];
            v = flights[i][1];
            w = flights[i][2];
            g[u].push_back({v,w});
        }

        for(int i = 0; i < n; ++i)
            mem[i] = vector<int>(K+1,-1);

        reachedDst = false;
        int ans = dfs(src,g,0,K,dst);
        if( !reachedDst ) return -1;
        return ans;
    }
};
