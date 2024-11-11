
// 3241. Time Taken to Mark All Nodes
// https://leetcode.com/problems/time-taken-to-mark-all-nodes/





class Solution {
private:


    int dfs(vector<int> t[], unordered_set<int> unknown[], int u, int src, int mx[]) {
        // cout << "dfs u " << u << " src " << src << endl;

        if( t[u].size() == 1 && src != -1 )
            return 0;

        // our slowest child:  mx[4*u]   time, mx[4*u+1] child
        // our second slowest: mx[4*u+2] time, mx[4*u+3] child

        for(auto it = unknown[u].begin(); it != unknown[u].end(); ) {
            int v = *it;
            if( v == src ) {
                ++it;
                continue;
            }

            int offset = v % 2 ? 1 : 2;
            int duration = offset + dfs(t, unknown, v, u, mx);

            if( duration > mx[4*u] ) {
                // push current slowest child down
                mx[4*u+2] = mx[4*u];
                mx[4*u+3] = mx[4*u+1];
                // set slowest child
                mx[4*u] = duration;
                mx[4*u+1] = v;
            } else if( duration > mx[4*u+2] ) {
                // set second slowest child
                mx[4*u+2] = duration;
                mx[4*u+3] = v;
            }

            it = unknown[u].erase(it);
        }
        /*
        cout << "dfs u " << u << " src " << src << " after " << endl;
        cout << "    slowest child        " << mx[4*u+1] << " time " << mx[4*u] << endl;
        cout << "    second slowest child " << mx[4*u+3] << " time " << mx[4*u+2] << endl;
        */

        return src == mx[4*u+1] ? mx[4*u+2] : mx[4*u];
    }

public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;

        // at each node we will hold the max and second to max answer and the respective child node taking that long
        // at each node we will hold for which child we don't know the answer yet

        // undirected tree
        vector<int> t[n];
        unordered_set<int> unknown[n];

        for(vector<int>& edge: edges) {
            int u = edge[0];
            int v = edge[1];

            t[u].push_back(v);
            unknown[u].insert(v);

            t[v].push_back(u);
            unknown[v].insert(u);
        }

        int mx[4*n];memset(mx,-1,sizeof mx);

        vector<int> ans(n);

        for(int u = 0; u < n; ++u)
            ans[u] = dfs(t, unknown, u, -1, mx);

        return ans;
    }
};
