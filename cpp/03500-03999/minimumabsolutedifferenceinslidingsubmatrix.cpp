
// 3567. Minimum Absolute Difference in Sliding Submatrix
// https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/




class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // TODO we could optimize by going down and then up
        // to avoid resetting mp

        int ans_rows = m-k+1;
        int ans_cols = n-k+1;
        vector<vector<int>> ans(ans_rows, vector<int>(ans_cols));

        for(int jj = 0; jj < ans_cols; ++jj) {
            cout << "jj " << jj << endl;
            map<int,int> mp;
            map<int,int> diffs;

            for(int i = 0; i < m; ++i) {
                for(int j = jj; j < jj + k; ++j) {
                    auto p = mp.insert({grid[i][j],1});
                    // cout << "i " << i << " j " << j << " " << grid[i][j] << " added" << endl;
                    if( !p.second ) {
                        ++p.first->second;
                    }
                    if( p.first != mp.begin() ) {
                        int diff = p.first->first - (prev(p.first))->first;
                        // cout << "diff to next smaller " << diff << endl;
                        ++diffs[diff];
                    }
                    if( next(p.first) != mp.end() ) {
                        int diff = (next(p.first))->first - p.first->first;
                        // cout << "diff to next greater " << diff << endl;
                        ++diffs[diff];
                    }
                    if( p.first != mp.begin() && next(p.first) != mp.end() ) {
                        int diff = (next(p.first))->first - (prev(p.first))->first;
                        --diffs[diff];
                        if( diffs[diff] == 0 )
                            diffs.erase(diff);
                    }
                }
                if( i >= k-1 ) {
                    /*
                    cout << "i " << i << " jj " << jj << endl;
                    for(auto p : mp) {
                        cout << p.first << ":" << p.second << " ";
                    }
                    cout << endl;
                    */
                    if( mp.size() > 1 )
                        ans[i-k+1][jj] = diffs.begin()->first;
                    for(int j = jj; j < jj + k; ++j) {
                        auto f = mp.find(grid[i-k+1][j]);
                        if( f != mp.begin() ) {
                            int diff = f->first - (prev(f))->first;
                            --diffs[diff];
                            if( diffs[diff] == 0 )
                                diffs.erase(diff);
                        }
                        if( next(f) != mp.end() ) {
                            int diff = (next(f))->first - f->first;
                            --diffs[diff];
                            if( diffs[diff] == 0 )
                                diffs.erase(diff);
                        }
                        if( f != mp.begin() && next(f) != mp.end() ) {
                            int diff = (next(f))->first - (prev(f))->first;
                            ++diffs[diff];
                        }
                        --f->second;
                        if( f->second == 0 )
                            mp.erase(f);
                    }
                }
            }
        }

        return ans;
    }
};
