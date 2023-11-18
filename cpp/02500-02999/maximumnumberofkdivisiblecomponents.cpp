
// 2872. Maximum Number of K-Divisible Components
// https://leetcode.com/problems/maximum-number-of-k-divisible-components/




/* topology of the tree matters
 * n
 * edges
 * values
 * k
 * example A answer 1
 * 5
 * [[0,1],[0,2],[0,3],[0,4]]
 * [5,4,1,4,1]
 * 5
 * example B answer 3 (same n, values (array of values is the same), k as A)
 * 5
 * [[0,1],[1,2],[2,3],[3,4]]
 * [5,4,1,4,1]
 * 5
 */
class Solution {
    int ans;

    long dfs(vector<int> g[], int u, int src, vector<int>& values, long k) {


        long sum = values[u];
        // if the sum of my children (if any) and me is divisible by k,
        // then we can form a component, and our parent does not have
        // to worry about us.
        // how to communicate that to our parent though? we don't have to.
        // because what we bubble up is divisible by k.

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( v == src )
                continue;
            sum += dfs(g,v,u,values,k);
        }

        if( sum % k == 0 )
            ++ans;

        return sum;
    }


public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        // it is guaranteed that the sum of values is divisible by k

        // undirected 'tree'
        vector<int> g[n];
        for(auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        ans = 0;
        // arbitrarily root the tree in node 0
        dfs(g,0,-1,values,k);

        return ans;
    }
};
