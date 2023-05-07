
// 2282. Number of People That Can Be Seen in a Grid
// https://leetcode.com/problems/number-of-people-that-can-be-seen-in-a-grid/




class Solution {
public:
    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();

        vector<vector<int>> ans(m,vector<int>(n,0));

        // rows
        for(int i = 0; i < m; ++i) {

            stack<int> stck; // monotonically increasing stack
            stck.push(heights[i][n-1]);

            for(int j = n-2; j >= 0; --j) {
                // as we are not in the rightmost column,
                // we can at minimum see our right neighbor

                int t = 0;

                while( !stck.empty() && stck.top() < heights[i][j] ) {
                    ++t;
                    stck.pop();
                }

                if( !stck.empty() )
                    ++t;

                ans[i][j] = t;

                if( !stck.empty() && stck.top() == heights[i][j] )
                    stck.pop();

                stck.push(heights[i][j]);
            }
        }


        // cols
        for(int j = 0; j < n; ++j) {

            stack<int> stck; // monotonically increasing stack
            stck.push(heights[m-1][j]);

            for(int i = m-2; i >= 0; --i) {
                // as we are not in the bottommost row,
                // we can at minimum see our below neighbor

                int t = 0;

                while( !stck.empty() && stck.top() < heights[i][j] ) {
                    ++t;
                    stck.pop();
                }

                if( !stck.empty() )
                    ++t;

                ans[i][j] += t;

                if( !stck.empty() && stck.top() == heights[i][j] )
                    stck.pop();

                stck.push(heights[i][j]);
            }
        }


        return ans;
    }
};
