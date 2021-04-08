
// 1443. Minimum Time to Collect All Apples in a Tree
// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/





class Solution {
private:

    int dfs(vector<int> t[], int curr, vector<bool>& hasApple, int seen[]) {
        if( seen[curr] ) return 0;
        seen[curr] = 1;

        // traverse each child
        int ans = 0;
        vector<int> children = t[curr];
        for(int i = 0; i < children.size(); ++i) {
            if( !seen[children[i]] )
                ans += dfs(t,children[i],hasApple,seen);
        }

        if( ans != 0 ) return curr == 0 ? ans : ans+2;
        if( hasApple[curr] ) return curr == 0 ? 0 : 2;
        return 0;
    }




public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        if( n < 2 ) return 0;

        vector<int> t[n]; // tree
        int seen[n];memset(seen,0,sizeof seen);
        for(int i = 0; i < edges.size(); ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }

        return dfs(t,0,hasApple,seen);
    }
};
