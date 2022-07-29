
// 2050. Parallel Courses III
// https://leetcode.com/problems/parallel-courses-iii/




class Solution {
private:
    void dfs(vector<int> g[], int u, int seen[], stack<int>& stck) {

        seen[u] = 1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // directed acyclic graph, nodes numbered 1 to n
        vector<int> g[n+1];
        for(auto& relation : relations)
            g[relation[0]].push_back(relation[1]);

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[n+1];memset(seen,0,sizeof seen);
        for(int u = 1; u < n+1; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // 'traverse' the graph in topological order keeping track
        // of the longest time to reach each node

        int ans = 0;

        // we will re-use seen to record the time
        memset(seen,0,sizeof seen);
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            int d = time[u-1]; // number of months it takes to complete course u
            int t = seen[u];   // number of months it took us to reach course u

            if( g[u].empty() ) {
                // terminal course
                // we need to add the time it takes to complete the course
                // to the time it took us to get here
                ans = max(ans,d+t);
                continue;
            }
            for(int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i];
                if( seen[v] < d + t ) {
                    seen[v] = d + t;
                    ans = max(ans,d + t);
                }
            }
        }

        return ans;
    }
};
