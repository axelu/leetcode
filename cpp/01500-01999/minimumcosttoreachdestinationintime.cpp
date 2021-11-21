
// 1928. Minimum Cost to Reach Destination in Time
// https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/




class Solution {
private:
    int n;

    int rec(vector<array<int,2>> G[], int u, int time, int maxTime,
            vector<int>& passingFees, int mem[]) {

        if( time > maxTime )    // we ran out of time
            return INT_MAX;

        if( u == n-1 ) {        // we arrived at node n-1
            return passingFees[u];
        }

        int memIdx = u*(maxTime+1)+time;
        if( mem[memIdx] != -1 )
            return mem[memIdx];

        // cout << "u " << u << " time " << time << endl;

        int ret = INT_MAX;

        int v,t;
        for(int i = 0; i < G[u].size(); ++i) {
            v = G[u][i][0];
            t = G[u][i][1];

            ret = min(ret,rec(G,v,time+t,maxTime,passingFees,mem));

        }

        if( ret != INT_MAX )
            ret += passingFees[u];

        return mem[memIdx] = ret;
    }


public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        n = passingFees.size();


        int i,u,v,time;

        // getting rid of duplicate edges, only keeping the fastest edge
        sort(edges.begin(),edges.end(),[](const vector<int>& a, const vector<int>& b){
            return a[2] < b[2];
        });
        int f[n][n];memset(f,0,sizeof f);

        // undirected weigthed graph
        vector<array<int,2>> G[n];
        for(i = 0; i < edges.size(); ++i) {
            u    = edges[i][0];
            v    = edges[i][1];
            time = edges[i][2];

            // have we seen this edge before?
            if( !f[u][v] ) {
                f[u][v] = 1;
                f[v][u] = 1;
                G[u].push_back({v,time});
                G[v].push_back({u,time});
            }
        }

        int mem[n*(maxTime+1)];
        for(i = 0; i < n*(maxTime+1); ++i)
            mem[i] = -1;

        // recursion + memoiation -> dp top-down
        int t = rec(G,0,0,maxTime,passingFees,mem);
        return t == INT_MAX ? -1 : t;

    }
};
