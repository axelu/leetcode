
// 1192. Critical Connections in a Network
// https://leetcode.com/problems/critical-connections-in-a-network/



// https://www.thealgorists.com/Algo/GraphTheory/Tarjan/Bridges
// Finding Bridges in a Connected Undirected Graph using Tarjan's Algorithm
class Solution {
private:
    void dfs(vector<int> g[], int seen[], vector<vector<int>>& ans,
             int u, int discoveryTimes[], int low[], int parent[], int& discoveryTime) {

        seen[u] = 1;
        ++discoveryTime;  // increment discovery time before assigning
        discoveryTimes[u] = discoveryTime;
        low[u] = discoveryTime;

        int v; // adjacent node
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];

            if( !seen[v]) {
                // the adjacent node is NOT an ancestor
                parent[v] = u;
                dfs(g,seen,ans,v,discoveryTimes,low,parent,discoveryTime);
                low[u] = min(low[u],low[v]);
            } else {
                // the adjacent node is an ancestor
                if( parent[u] != v) {
                    // the adjacent node is NOT the parent
                    low[u] = min(low[u],discoveryTimes[v]);
                }
            }
            if( low[v] > discoveryTimes[u]) {
                ans.push_back({u,v}); // bridge found
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        int discoveryTimes[n];
        int low[n]; // earliest discovered node reachable from node at idx
                    //     by not using backedge that goes through parent
        int parent[n];
        int seen[n]; memset(seen,0,sizeof seen);

        // construct an undirected graph
        vector<int> g[n];
        for(int i = 0; i < connections.size(); ++i) {
            g[connections[i][0]].push_back(connections[i][1]);
            g[connections[i][1]].push_back(connections[i][0]);
        }

        vector<vector<int>> ans;
        int discoveryTime = -1;
        dfs(g,seen,ans,0,discoveryTimes,low,parent,discoveryTime);
        return ans;
    }
};
