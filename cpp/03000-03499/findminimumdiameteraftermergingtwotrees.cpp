
// 3203. Find Minimum Diameter After Merging Two Trees
// https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/







class Solution {
private:
    int ans;

    int dfs(vector<int> g[], int u, int src, int depth) {
        if( g[u].size() == 1 && src != -1 )
            return depth;

        priority_queue<int> pq;
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( v == src )
                continue;
            int t = dfs(g, v, u, depth+1);
            pq.push(t);
        }

        // max depth reachable from this node
        int mx1 = 0;
        if( !pq.empty() ) {
            mx1 = pq.top();
            pq.pop();
        }
        if( mx1-depth > ans )
            ans = mx1-depth;
        // second largest depth reachable from this node
        if( !pq.empty() ) {
            int mx2 = pq.top();
            // longest path via the current node
            if( (mx1-depth)+(mx2-depth) > ans )
                ans = (mx1-depth)+(mx2-depth);
        }
        return mx1;
    }

    int get_diameter(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<int> g[n];
        for(auto v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        ans = 0;
        dfs(g, 0, -1, 0);

        return ans;
    }


public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        // both trees should be rooted in a node of theirs,
        // that gives the minimum max depth to any leave.
        // then we would connect those two roots

        int diameter1 = get_diameter(edges1); // cout << "diameter1 " << diameter1 << endl;
        int diameter2 = get_diameter(edges2); // cout << "diameter2 " << diameter2 << endl;

        int a = diameter1/2;
        if( diameter1 % 2 )
            ++a;

        int b = diameter2/2;
        if( diameter2 % 2 )
            ++b;

        return max({a + b + 1, diameter1, diameter2});
    }
};
