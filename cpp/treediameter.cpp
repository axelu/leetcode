
// 1245. Tree Diameter
// https://leetcode.com/problems/tree-diameter/



class Solution {
private:
    int maxDist;
    int furthestNode;

    void dfs(vector<int> t[], int seen[], int idx, int dist) {
        if( seen[idx] ) return;
        if( dist > maxDist ) {
            maxDist = dist;
            furthestNode = idx;
        }

        seen[idx] = 1;
        for(int i = 0; i < t[idx].size(); ++i) {
            dfs(t,seen,t[idx][i],dist+1);
        }
    }

public:
    int treeDiameter(vector<vector<int>>& edges) {
        size_t n = edges.size();
        if( n < 2 ) return n;

        vector<int> t[n+1];
        for(int i = 0; i < n; ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }

        int seen[n+1]; memset(seen,0,sizeof seen);
        // A to B
        maxDist = 0;
        dfs(t,seen,0,0);
        // B to C
        memset(seen,0,sizeof seen);
        maxDist = 0;
        dfs(t,seen,furthestNode,0);

        return maxDist;
    }
};
