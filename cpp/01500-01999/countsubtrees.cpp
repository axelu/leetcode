
// 1519. Number of Nodes in the Sub-Tree With the Same Label
// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/



class Solution {
private:
    int * dfs(int v, vector<int> t[], int seen[], string& labels, vector<int>& ans) {
        seen[v] = 1;
        int cnt[26]; memset(cnt,0,sizeof cnt);
        for(int i = 0; i < t[v].size(); ++i) {
            int childIdx = t[v][i];
            if( seen[childIdx] ) continue;
            int * childCount = dfs(childIdx,t,seen,labels,ans);
            // aggregate
            for(int j = 0; j < 26; ++j)
                cnt[j] += childCount[j];
        }
        ++cnt[labels[v]-'a'];
        ans[v] = cnt[labels[v]-'a'];
        return cnt;
    }

public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<int> ans(n,1);
        if( n == 1 ) return ans;

        vector<int> t[n];
        for(int i = 0; i < edges.size(); ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }
        int seen[n]; memset(seen,0,sizeof seen);
        dfs(0,t,seen,labels,ans);

        return ans;
    }
};
