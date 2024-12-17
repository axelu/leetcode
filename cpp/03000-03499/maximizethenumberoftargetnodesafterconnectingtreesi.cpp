
// 3372. Maximize the Number of Target Nodes After Connecting Trees I
// https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/





class Solution {
private:
    unordered_map<int,int> mem;

    int rec(vector<int> t[], int u, int src, int k) {
        if( k == 0 )
            return 1;

        int key = (u<<20) + (src<<10) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        int ret = 1; // our current node

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;

            ret += rec(t, v, u, k-1);
        }

        return mem[key] = ret;
    }

public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size() + 1; // 2 <= n <= 1000
        if( k == 0 ) {
            vector<int> v(n,1);
            return v;
        }

        int m = edges2.size() + 1; // 2 <= m <= 1000
        vector<int> t2[1000];
        for(auto& edge: edges2) {
            t2[edge[0]].push_back(edge[1]);
            t2[edge[1]].push_back(edge[0]);
        }

        // for tree 2 we are only interested in the max when k-1
        int mx = 1;
        for(int u = 0; u < m; ++u)
            mx = max(mx, rec(t2, u, 1000, k-1));

        // cout << mx << endl;

        vector<int> t1[1000];
        for(auto& edge: edges1) {
            t1[edge[0]].push_back(edge[1]);
            t1[edge[1]].push_back(edge[0]);
        }

        vector<int> ans(n);
        mem.clear();
        for(int u = 0; u < n; ++u) {
            int t = rec(t1, u, 1000, k);
            ans[u] = t + mx;
        }

        return ans;
    }
};
