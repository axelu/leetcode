
// 3820. Pythagorean Distance Nodes in a Tree
// https://leetcode.com/problems/pythagorean-distance-nodes-in-a-tree/



class Solution {
private:
    void rec(vector<vector<int>>& t, int u, int src, int depth, vector<int>& d) {
        d[u] = depth;
        for(int v: t[u]) {
            if( v != src )
                rec(t, v, u, depth+1, d);
        }
        return;
    }

public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
        vector<vector<int>> t(n); // undirected tree
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        // brute force
        // make three runs rooting t in x, y, z to record distance of all other nodes
        //    to x, y and z.
        // alternatively we could make one run only, and figure out LCA to calc distance


        vector<int> dx(n);
        rec(t, x, -1, 0, dx);
        vector<int> dy(n);
        rec(t, y, -1, 0, dy);
        vector<int> dz(n);
        rec(t, z, -1, 0, dz);

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            // (a*a) + (b*b) = (c*c)
            // a b c
            // a c b
            // b a c --
            // b c a
            // c a b --
            // c b a --

            long a2 = (long)dx[i] * (long)dx[i];
            long b2 = (long)dy[i] * (long)dy[i];
            long c2 = (long)dz[i] * (long)dz[i];

            if( a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2 )
                ++ans;
        }

        return ans;
    }
};
