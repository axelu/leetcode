
// 2503. Maximum Number of Points From Grid Queries
// https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/





class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int q_sz = queries.size();
        vector<int> ans(q_sz);


        // sort queries but need to know the index it was at
        vector<array<int,2>> _queries; // queries[i],i
        for(int i = 0; i < q_sz; ++i)
            _queries.push_back({queries[i],i});
        sort(_queries.begin(),_queries.end(),[](const array<int,2>& a, const array<int,2>& b){
            return a[0] < b[0];
        });

        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        pq.push({grid[0][0],0,0});
        bool seen[m][n];memset(seen,false,sizeof seen);
        seen[0][0] = true;

        int t = 0;

        int q_idx = 0;
        while( q_idx < q_sz ) {

            while( !pq.empty() && q_idx < q_sz && pq.top()[0] >= _queries[q_idx][0] ) {
                ans[_queries[q_idx][1]] = t;
                ++q_idx;
            }
            if( q_idx == q_sz )
                break;

            // current query val
            int q_val = _queries[q_idx][0];
            // cout << "q_val " << q_val << endl;

            while( !pq.empty() && pq.top()[0] < q_val ) {
                int i = pq.top()[1];
                int j = pq.top()[2];
                // cout << "grid_val " << grid[i][j] << " i " << i << " j " << j << endl;
                pq.pop();

                // collect the point
                ++t;

                // explore all 4 directions
                for(int k = 0; k < 4; ++k) {
                    int i_new = i + dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;

                    int j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    if( seen[i_new][j_new] )
                        continue;

                    seen[i_new][j_new] = true;
                    pq.push({grid[i_new][j_new],i_new,j_new});
                }
            }

            // enter answer for all queries with same query value
            while( q_idx < q_sz && _queries[q_idx][0] == q_val ) {
                ans[_queries[q_idx][1]] = t;
                ++q_idx;
            }

        }

        return ans;
    }
};
