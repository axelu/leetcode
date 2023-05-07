
// 1878. Get Biggest Three Rhombus Sums in a Grid
// https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/



class Solution {
private:

    int sum(vector<vector<int>>& grid, int i, int j, int k) {
        // i and j are the upper corner of the rhombus
        // k is the length of the rhombus

        int ret = grid[i][j];
        if( k > 0 ) {

            for(int o = 1; o <= k; ++o)
                ret += grid[i+o][j-o] + grid[i+o][j+o];

            ret += grid[i + 2*k][j];
            for(int o = i + 2*k - 1, d = 1; o > i + k; --o, ++d)
                ret += grid[o][j-d] + grid[o][j+d];

        }
        return ret;
    }

public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        set<int> st;

        // brute force
        for(int k = 0; k * 2 + 1 <= min(m,n); ++k) {
            //cout << "k " << k << endl;

            for(int i = 0; i <= m - (2*k+1); ++i) {
                for(int j = k; j <= n-1-k; ++j) {
                    //cout << "i " << i << " j " << j << endl;
                    st.insert(sum(grid,i,j,k));
                    if( st.size() > 3 )
                        st.erase(st.begin());
               }
            }
        }

        vector<int> ans;
        for(auto it = st.rbegin(); it != st.rend(); ++it)
            ans.push_back(*it);

        return ans;
    }
};
