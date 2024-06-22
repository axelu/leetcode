
// 2973. Find Number of Coins to Place in Tree Nodes
// https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/





/*  -infinity       0      infinity
 *   3 or more < 0                     product will be negative -> place 0
 *           2 < 0     1 > 0           take product off all three, will be positive
 *           1 < 0     2 > 0           product will be negative -> place 0
 *                     3 or more > 0   take product of greatest three, will be positive
 *                  0  3 total, one 0  product will be 0
 *   all other cases:
 *   x x ...........................x  two smallest < 0 * greatest positive
 *   ...........................x x x  poduct of three greatest > 0
 */
class Solution {
private:
    vector<long long> ans;
    int n;

    vector<int> merge(vector<int>& a, vector<int>& b) {
        int a_sz = a.size();
        int b_sz = b.size();
        vector<int> res(a_sz + b_sz);

        int i = 0, j = 0, k = 0;
        while( i < a_sz && j < b_sz ) {
            if( a[i] < b[j] ) {
                res[k] = a[i];
                ++i;
            } else {
                res[k] = b[j];
                ++j;
            }
            ++k;
        }
        while( i < a.size() ) {
            res[k] = a[i];
            ++i;
            ++k;
        }
        while( j < b.size() ) {
            res[k] = b[j];
            ++j;
            ++k;
        }

        return res;
    }

    vector<int> rec(vector<int> g[], int u, int src, vector<int>& cost) {
        vector<int> ret{cost[u]};

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( v == src )
                continue;

            auto t = rec(g,v,u,cost);
            ret = merge(ret,t);
        }

        // place coins
        int ret_sz = ret.size();
        if( ret_sz < 3 ) {
            ans[u] = 1;
            return ret;
        } else if( ret_sz == 3 ) {
            long long res = (long long)ret[0] * (long long)ret[1] * (long long)ret[2];
            ans[u] = res < 0 ? 0LL : res;
            return ret;
        } else {
            long long a = max(0LL, (long long)ret[0] * (long long)ret[1] * (long long)ret[ret_sz - 1]);
            long long b = max(0LL, (long long)ret[ret_sz - 3] * (long long)ret[ret_sz - 2] * (long long)ret[ret_sz -1]);
            ans[u] = max(a,b);
            if( ret_sz <= 5 )
                return ret;
            return {ret[0], ret[1], ret[ret_sz - 3], ret[ret_sz - 2], ret[ret_sz -1]};
        }

        return ret;
    }


public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        n = cost.size(); // cost.length == n; edges.length == n - 1
        ans.resize(n);

        vector<int> g[n];
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        rec(g,0,-1,cost);
        return ans;
    }
};
