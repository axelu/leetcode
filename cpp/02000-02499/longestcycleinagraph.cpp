
// 2360. Longest Cycle in a Graph
// https://leetcode.com/problems/longest-cycle-in-a-graph/



class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();

        int seen[n];memset(seen,0,sizeof seen);

        int ans = -1;

        for(int i = 0; i < n; ++i) {
            if( seen[i] )
                continue;

            // explore starting from i
            int u = i;
            seen[u] = 1;
            int step = 0;
            unordered_map<int,int> cycle; // node,step
            cycle[u] = step;
            while( edges[u] != -1 && seen[edges[u]] == 0 ) {
                ++step;
                u = edges[u];
                seen[u] = 1;
                cycle[u] = step;
            }
            auto f = cycle.find(edges[u]);
            if( f != cycle.end() )
                ans = max(ans,step - f->second + 1);
        }

        return ans;
    }
};
