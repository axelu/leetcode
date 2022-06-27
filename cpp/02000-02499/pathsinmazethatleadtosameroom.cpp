
// 2077. Paths in Maze That Lead to Same Room
// https://leetcode.com/problems/paths-in-maze-that-lead-to-same-room/




class Solution {
private:
    int ans;
    int roads[1001][1001];
    int seen[1001];

    void dfs(vector<int> g[], int u) {

        seen[u] = 1; // mark as seen

        int gu_sz = g[u].size();
        for(int i = 0; i < gu_sz-1; ++i)
            for(int j = i+1; j < gu_sz; ++j)
                // checking seen to avoid double counting
                if( !seen[g[u][i]] && !seen[g[u][j]] && roads[g[u][i]][g[u][j]] )
                    ++ans;

        for(int i = 0; i < gu_sz; ++i)
            if( !seen[g[u][i]] )
                dfs(g,g[u][i]);
    }

public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        // cout << "corridors.size() " << corridors.size() << endl;
        vector<int> g[n+1];

        memset(roads,0,sizeof roads);

        for(auto& v : corridors) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
            roads[v[0]][v[1]] = 1;
            roads[v[1]][v[0]] = 1;
        }

        ans = 0;

        memset(seen,0,sizeof seen);
        for(int i = 1; i <= n; ++i)
            if( !seen[i] )
                dfs(g,i);

        return ans;
    }
};
