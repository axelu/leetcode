
// 2493. Divide Nodes Into the Maximum Number of Groups
// https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/




class Solution {
private:
    void dfs(vector<int> g[], int u, int seen[], vector<vector<int>>& ccs, int ccid) {
        seen[u] = 1;
        ccs[ccid].push_back(u);

        for(int v: g[u]) {
            if( seen[v] )
                continue;
            dfs(g,v,seen,ccs,ccid);
        }

        return;
    }

public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<int> g[n+1];
        for(auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        vector<vector<int>> ccs; // connected components cc
        int ccid = 0;
        int seen[n+1];memset(seen,0,sizeof seen);
        for(int u = 1; u <= n; ++u) {
            if( !seen[u] ) {
                vector<int> cc;
                ccs.push_back(cc);
                dfs(g,u,seen,ccs,ccid);
                ++ccid;
            }
        }

        int ans = 0;

        for(auto& cc: ccs) {

            // for each connected component, we will try
            // each node as the root using bfs
            int mx_group = -1;
            for(int root: cc) {
                bool has_valid_grouping = true;
                memset(seen,0,sizeof seen);
                queue<array<int,2>> q;
                q.push({root,1});
                seen[root] = 1;
                int group = 1;
                while( !q.empty() && has_valid_grouping) {

                    queue<array<int,2>> q_new;
                    while( !q.empty() && has_valid_grouping ) {
                        int u = q.front()[0];
                        group = q.front()[1];
                        q.pop();

                        for(int v: g[u]) {
                            if( seen[v] ) {
                                if( (seen[v] == group - 1) ||  (seen[v] == group + 1) ) {
                                    continue;
                                } else {
                                    has_valid_grouping = false;
                                    break;
                                }
                            }
                            seen[v] = group + 1;
                            q_new.push({v,group+1});
                        }
                    }
                    if( has_valid_grouping )
                        swap(q,q_new);
                }
                if( has_valid_grouping )
                    mx_group = max(mx_group, group);
            }
            if( mx_group == -1 )
                return -1;
            ans += mx_group;
        }

        return ans;
    }
};
