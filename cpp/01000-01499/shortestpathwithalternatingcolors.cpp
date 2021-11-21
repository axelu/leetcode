
// 1129. Shortest Path with Alternating Colors
// https://leetcode.com/problems/shortest-path-with-alternating-colors/




class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        int i;

        vector<int> rg[n]; // red  graph adjacency list
        vector<int> bg[n]; // blue graph adjacency list

        for(i = 0; i < red_edges.size(); ++i)
            rg[red_edges[i][0]].push_back(red_edges[i][1]);
        for(i = 0; i < blue_edges.size(); ++i)
            bg[blue_edges[i][0]].push_back(blue_edges[i][1]);

        // BFS
        queue<array<int,3>> q; // node,color,step; color 0 red, blue 1
        int seen[n][2];memset(seen,0,sizeof seen);
        q.push({0,0,0}); // starting from red exploring blue edges next
        seen[0][0] = 1;
        q.push({0,1,0}); // starting from blue exploring red edges next
        seen[0][1] = 1;
        vector<int> ans(n,-1);
        ans[0] = 0;
        int u,v,color,color_new,step;
        vector<int> * g;
        while(!q.empty()) {
            u     = q.front()[0];
            color = q.front()[1]; // color of edge last traveled
            step  = q.front()[2];
            q.pop();

            if( color == 0 ) {
                g = bg;
                color_new = 1;
            } else {
                g = rg;
                color_new = 0;
            }

            for(i = 0; i < g[u].size(); ++i) {
                v = g[u][i];

                if( ans[v] == -1 )
                    ans[v] = step+1;

                if( seen[v][color_new] )
                    continue;

                seen[v][color_new] = 1;
                q.push({v,color_new,step+1});
            }
        }

        return ans;
    }
};
