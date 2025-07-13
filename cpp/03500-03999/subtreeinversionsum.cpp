
// 3544. Subtree Inversion Sum
// https://leetcode.com/problems/subtree-inversion-sum/



class Solution {
private:
    // node 50000, k 51, parity 2

    // long long mem[50000][51][2];
    vector<vector<vector<long long>>> mem;

    long long rec(vector<vector<int>>& t, vector<int>& nums,
                  int u, int src, bool inverted, int edges_since_inversion, int k) {

        if( mem[u][edges_since_inversion][inverted] != -1LL )
            return mem[u][edges_since_inversion][inverted];

        // we have a choice
        //    don't invert OR
        //    invert if we can aka if we are far enough from last inversion
        // Note: if we arrive inverted, and then invert, we are our normal
        // inverted invert
        //    0        0     normal
        //    1        0     inverted
        //    0        1     inverted
        //    1        1     normal

        long long val = inverted ? -nums[u] : nums[u];

        long long a = val;

        bool can_invert = edges_since_inversion == k;
        long long b = LLONG_MIN;
        if( can_invert )
            b = -val;

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;

            // don't invert
            a += rec(t, nums, v, u, inverted, min(k, edges_since_inversion + 1), k);

            // invert if we can
            if( can_invert )
                b += rec(t, nums, v, u, !inverted, 1, k);
        }

        return mem[u][edges_since_inversion][inverted] = max(a,b);
    }

public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        // undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1
        int n = edges.size() + 1;

        // edge case
        // but also shows the logic for more than 2 nodes
        if( n == 2 ) {
            // 2 nodes 1 edge
            // don't invert
            long long a = nums[0] + nums[1];
            // invert don't invert
            long long b = -nums[0] - nums[1];
            // invert invert if we can
            long long c = LLONG_MIN;
            if( k == 1 )
                c = -nums[0] + nums[1];
            // don't invert invert
            long long d = nums[0] - nums[1];
            return max({a,b,c,d});
        }

        vector<vector<int>> t(n);
        for(auto& edge :edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        // memset(mem,-1,sizeof mem);
        mem.assign(n, vector<vector<long long>>(k+1, vector<long long>(2,-1LL)));
        return rec(t, nums, 0, -1, false, k, k);
    }
};
