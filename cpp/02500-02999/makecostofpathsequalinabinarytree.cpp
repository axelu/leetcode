
// 2673. Make Costs of Paths Equal in a Binary Tree
// https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/




class Solution {
private:
    int dfs(int n, vector<int>& cost, int i, vector<pair<int,int>>& children) {
        if( i > n )
            return 0;

        int cur = cost[i-1];
        int l = dfs(n,cost,2*i,children);
        int r = dfs(n,cost,2*i+1,children);

        children[i-1] = {l,r};
        return cur + max(l,r);
    }

    int solve(int n, vector<int>& cost, int i, vector<pair<int,int>>& children, int target) {
        if( i > n )
            return 0;

        // at the current node, we need to deliver target cost
        // said differently: all path from us to all leafs under us, need to cost target

        // how much does the current node contribute?
        int t = target - cost[i-1];

        // can we increment at our current node and if so, by how much?
        int incr = t - max(children[i-1].first,children[i-1].second);

        int lincr = solve(n,cost,2*i,children, target - cost[i-1] - incr);
        int rincr = solve(n,cost,2*i+1,children, target - cost[i-1] - incr);

        return incr + lincr + rincr;
    }

public:
    int minIncrements(int n, vector<int>& cost) {
        // get the most expensive path
        // at each node, keep track of what the left and right child contribute
        vector<pair<int,int>> children(n);
        int mx = dfs(n,cost,1,children);

        return solve(n,cost,1,children,mx);
    }
};
