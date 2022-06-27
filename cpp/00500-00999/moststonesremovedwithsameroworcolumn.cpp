
// 947. Most Stones Removed with Same Row or Column
// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/



class Solution {
private:
    void dfs(vector<int> g[], int u, int seen[]) {
        seen[u] = 1;
        for(int v : g[u])
            if( !seen[v] )
                dfs(g,v,seen);
    }

public:
    int removeStones(vector<vector<int>>& stones) {
        // let a node be a cell with with a stone
        // create a bidirectional graph between adjacent nodes
        // adjacent here means along the row or column

        // what we are after is the number of connected components
        // ans = number of stones - number of connected components
        // because 1 stone per connected component will be left

        int n = stones.size(); // number of stones

        vector<int> g[n]; // bidirectional graph

        vector<int> by_col[10001];
        // sort stones by row and col
        sort(stones.begin(),stones.end());
        int prev_row = -1;
        for(int i = 0; i < n; ++i) {
            int row = stones[i][0];
            int col = stones[i][1];
            if( row != prev_row ) {
                // left most node in row so we cannot connect it
                // yet with another node in the same row
                prev_row = row;
            } else {
                // the previous node i-1 is in the same row
                // let us connect them
                g[i-1].push_back(i);
                g[i].push_back(i-1);
            }
            // have we seen a node in the same column?
            if( !by_col[col].empty() ) {
                g[by_col[col].back()].push_back(i);
                g[i].push_back(by_col[col].back());
            }
            by_col[col].push_back(i);
        }

        // DFS
        int seen[n];memset(seen,0,sizeof seen);
        int cc = 0; // number of connected components
        for(int i = 0; i < n; ++i) {
            if( !seen[i] ) {
                ++cc;
                dfs(g,i,seen);
            }
        }

        return n-cc;
    }
};
