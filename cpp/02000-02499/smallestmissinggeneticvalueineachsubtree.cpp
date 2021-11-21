
// 2003. Smallest Missing Genetic Value in Each Subtree
// https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/





class Solution {
private:
    void dfs(vector<int> g[], int u, vector<int>& nums, int seen[]) {
        if( seen[nums[u]] )
            return;

        seen[nums[u]] = 1;
        int v;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];
            dfs(g,v,nums,seen);
        }
    }

public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size(); // n == parents.length == nums.length


        // build the tree
        // also find node with value of 1
        vector<int> g[n];
        int u = nums[0] == 1 ? 0 : -1;  // node with value = 1
        for(int i = 1; i < n; ++i) {
            g[parents[i]].push_back(i);

            if( nums[i] == 1 )
                u = i;

        }

        // the answer for all nodes is 1, unless
        // a node is in the path starting from
        // the node with value of 1 to the root
        vector<int> ans(n,1);
        // if there is no node with value of 1,
        // then the answer for all nodes is 1
        if( u == -1 )
            return ans;

        // explore all descendents for every node starting
        // from the node with value of 1 to the root
        int mn = 1;
        int seen[100002];memset(seen,0,sizeof seen);
        for(; u != -1; u = parents[u] ) {
            dfs(g,u,nums,seen);
            while( seen[mn] )
                ++mn;
            ans[u] = mn;
        }

        return ans;
    }
};
