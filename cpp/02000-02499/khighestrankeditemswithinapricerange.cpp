
// 2146. K Highest Ranked Items Within a Price Range
// https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/



class Solution {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        // rank by:
        //     distance from start asc - shorter distance has higher rank
        //     price asc - lower price has higher rank
        //     row asc - smaller row has higher rank
        //     col asc - smaller column has higher rank

        int m = grid.size();     // rows
        int n = grid[0].size();  // cols

        vector<vector<int>> v; // inner vector: dist, price, row, col

        // BFS
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        pq.push({0,start[0],start[1]});

        int seen[m*n];memset(seen,0,sizeof seen);
        int seenIdx = start[0] * n + start[1];
        seen[seenIdx] = 1;

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        int price_mn = pricing[0];
        int price_mx = pricing[1];

        while( !pq.empty() ) {
            auto[dist,i,j] = pq.top();
            pq.pop();

            // harvest the current cell
            if( grid[i][j] >= price_mn && grid[i][j] <= price_mx )
                v.push_back({dist,grid[i][j],i,j});

            // explore all four directions
            for(int l = 0; l < 4; ++l) {
                int i_new = i + dirR[l];
                if( i_new < 0 || i_new == m )
                    continue;

                int j_new = j + dirC[l];
                if( j_new < 0 || j_new == n )
                    continue;

                // is it a wall?
                if( grid[i_new][j_new] == 0 )
                    continue;

                // have we seen it already?
                seenIdx = i_new * n + j_new;
                if( seen[seenIdx] )
                    continue;

                seen[seenIdx] = 1;
                pq.push({dist+1,i_new,j_new});
            }
        }

        // sort v
        sort(v.begin(),v.end());
        // extract ans from v
        vector<vector<int>> ans;
        int v_sz = v.size();
        for(int i = 0; i < min(v_sz,k); ++i)
            ans.push_back({v[i][2],v[i][3]});

        return ans;
    }
};
