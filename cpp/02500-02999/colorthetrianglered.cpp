
// 2647. Color the Triangle Red
// https://leetcode.com/problems/color-the-triangle-red/





/* solution based on the two hints provided in the problem
 * and on trying n=7 and n=8
 */
class Solution {
public:
    vector<vector<int>> colorRed(int n) {
        vector<vector<int>> ans;

        for(int i = n; i >= 2; ) {
            // working in set of rows 4 at a time bottom up
            for(int j = 1; j <= i*2 - 1; j += 2)
                ans.push_back({i,j});
            if( --i == 1 )
                break;
            ans.push_back({i,2});
            if( --i == 1 )
                break;
            for(int j = 3; j <= i*2 - 1; j += 2)
                ans.push_back({i,j});
            if( --i == 1 )
                break;
            ans.push_back({i,1});
            --i;
        }
        // finish up - add the tip
        ans.push_back({1,1});

        return ans;
    }
};
