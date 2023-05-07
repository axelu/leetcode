
// 1727. Largest Submatrix With Rearrangements
// https://leetcode.com/problems/largest-submatrix-with-rearrangements/




class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();      // rows
        int n = matrix[0].size();   // cols

        int ans = 0;

        // we will row by row keep track of the
        // consecutive 1s seen in each column up to that row,
        // basically in the current row we know how many
        // consecitive 1s are upwards in each column
        vector<int> heights(n,0);
        for(int i = 0; i < m; ++i) {        // row
            for(int j = 0; j < n; ++j) {    // col
                if( matrix[i][j] == 1 )
                    heights[j] += 1;
                else
                    heights[j] = 0;
            }

            // we can swap columns
            // sort heights of the current row desc
            // then we could create a rectangle
            // of a given width with the min height of 'width' highest columns
            // example
            // let the current row have 'consecutive 1s heights' as follows
            // {2,4,7,0,1} => sort desc:         {7,4,2,1,0}
            // rectangle area with width = 1: min{7}         * 1 = 7
            // rectangle area with width = 2: min{7,4}       * 2 = 8
            // rectangle area with width = 3: min{7,4,2}     * 3 = 6
            // rectangle area with width = 4: min{7,4,2,1}   * 4 = 4
            // rectangle area with width = 4: min{7,4,2,1,0} * 5 = 0 we can break if height is 0

            vector<int> t = heights;
            sort(t.begin(),t.end(),greater<int>());
            int mn_height = t[0];
            for(int k = 0; k < n; ++k) {
                if( t[k] == 0 )
                    break;
                mn_height = min(mn_height,t[k]);
                ans = max(ans,mn_height * (k+1));
            }
        }

        return ans;
    }
};
