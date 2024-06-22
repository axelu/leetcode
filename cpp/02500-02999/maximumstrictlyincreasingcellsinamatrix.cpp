
// 2713. Maximum Strictly Increasing Cells in a Matrix
// https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/




class Solution {
private:
    int upper_bound(vector<pair<int,int>>& nums, int n, int target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid].first )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s].first <= target )
            ++s;

        return s;
    }

    int rec(const vector<vector<int>>& mat, int m, int n,
            vector<pair<int,int>> rows[], vector<pair<int,int>> cols[],
            const int i, const int j, int mem[]) {

        // cout << "rec i " << i << " j " << j << endl;

        int mem_idx = i * n + j;
        if( mem[mem_idx] != -1 )
            return mem[mem_idx];

        // if we got here, we 'visited' the current cell,
        // hence returning 1 at minimum
        int ret = 1;

        int val = mat[i][j];

        // same row find next greater value
        int col_idx = upper_bound(rows[i],n,val);
        if( col_idx < n ) {
            int nxt_val = rows[i][col_idx].first;
            for(; col_idx < n && rows[i][col_idx].first == nxt_val; ++col_idx)
                ret = max(ret, 1 + rec(mat,m,n,rows,cols,i,rows[i][col_idx].second,mem));
        }

        // same col find next greater value
        int row_idx = upper_bound(cols[j],m,val);
        if( row_idx < m ) {
            int nxt_val = cols[j][row_idx].first;
            for(; row_idx < m && cols[j][row_idx].first == nxt_val; ++row_idx)
                ret = max(ret, 1 + rec(mat,m,n,rows,cols,cols[j][row_idx].second,j,mem));
        }

        return mem[mem_idx] = ret;
    }


public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size(); // rows
        int n = mat[0].size(); // cols
        // cout << "m " << m << " n " << n << endl;

        // edge case
        // if m == 1 or n == 1, then the answer is number of distinct values
        if( m == 1 || n == 1 ) {
            unordered_set<int> us;
            for(int i = 0; i < m; ++i)
                for(int j = 0; j < n; ++j)
                    us.insert(mat[i][j]);
            return us.size();
        }

        // as we can only go to cells that are strictly greater,
        // we don't need to worry about going backwards repeating a path

        vector<pair<int,int>> rows[m];
        for(int i = 0; i < m; ++i) {
            vector<pair<int,int>> v(n);
            for(int j = 0; j < n; ++j)
                v[j] = {mat[i][j],j};
            sort(v.begin(),v.end(),[](const pair<int,int>& a, const pair<int,int>& b){
               return a.first < b.first;
            });
            rows[i] = v;
        }

        vector<pair<int,int>> cols[n];
        for(int j = 0; j < n; ++j) {
            vector<pair<int,int>> v(m);
            for(int i = 0; i < m; ++i)
                v[i] = {mat[i][j],i};
            sort(v.begin(),v.end(),[](const pair<int,int>& a, const pair<int,int>& b){
               return a.first < b.first;
            });
            cols[j] = v;
        }

        int ans = 1;
        int mem[m*n];memset(mem,-1,sizeof mem);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                int mem_idx = i * n + j;
                if( mem[mem_idx] != -1 )
                    continue;
                // cout << "from main to rec i " << i << " j " << j << endl;
                ans = max(ans, rec(mat,m,n,rows,cols,i,j,mem));
            }
        }

        return ans;
    }
};
