
// 3004. Maximum Subtree of the Same Color
// https://leetcode.com/problems/maximum-subtree-of-the-same-color/





class Solution {
private:
    int ans;

    int dfs(vector<int> t[], int u, int src, vector<int>& colors) {
        int subtree_sz = 0;
        bool same_color_subtree = true;
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;

            int subtree = dfs(t,v,u,colors);
            if( subtree == -1 )
                same_color_subtree = false;
            else
                subtree_sz += subtree;
        }

        if( same_color_subtree )
            ans = max(ans, subtree_sz + 1);

        if( same_color_subtree && u > 0 && colors[u] == colors[src] )
            return subtree_sz + 1;

        return -1;
    }

public:
    int maximumSubtreeSize(vector<vector<int>>& edges, vector<int>& colors) {
        int n = colors.size();

        vector<int> t[n]; // tree rooted in 0
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        ans = 1;
        dfs(t,0,-1,colors);
        return ans;
    }
};
