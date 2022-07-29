
// 2277. Closest Node to Path in Tree
// https://leetcode.com/problems/closest-node-to-path-in-tree/



class Solution {
private:
    bool dfs(vector<int> g[], int u, int dest, int path[]) {
        if( u == dest )
            return true;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( path[v] )
                continue;

            path[v] = 1;
            if( dfs(g,v,dest,path) )
                return true;

            // backtrack
            path[v] = 0;
        }

        return false;
    }

    int bfs(vector<int> g[], int n, int dest[], int start) {
        int seen[n];memset(seen,0,sizeof seen);
        queue<int> q;
        q.push(start);
        seen[start] = 1;
        while( !q.empty() ) {
            int u = q.front();
            q.pop();

            if( dest[u] )
                return u;

            for(int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i];
                if( seen[v] )
                    continue;

                seen[v] = 1;
                q.push(v);
            }
        }

        return -1;
    }

public:
    vector<int> closestNode(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // the 'tree' can be rooted in any node
        // idea:
        //     BFS from start and end, at the first node discovered from both directions
        //     only continue to record the path discovered by the opposite start
        //     that is the path between start and end
        //     if the query node was part of the path, the answer is 0
        //     otherwise BFS from query node till a node in the path is discovered

        vector<int> g[n];
        for(auto& v : edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int q_sz = query.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {

            // BFS from start and end
            int start = query[i][0];
            int end   = query[i][1];
            int qnode = query[i][2];

            if( start == qnode || end == qnode ) {
                ans[i] = qnode;
                continue;
            } else if( start == end ) {
                ans[i] = start;
            } else {
                int path[n];memset(path,0,sizeof path);
                path[start] = 1;
                dfs(g,start,end,path);
                /*
                for(int k = 0; k < n; ++k)
                    if( path[k] )
                        cout << k << " ";
                cout << endl;
                */
                if( path[qnode] ) {
                    ans[i] = qnode;
                } else {
                    ans[i] = bfs(g,n,path,qnode);
                }
            }
        }

        return ans;
    }
};
