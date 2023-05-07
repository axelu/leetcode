
// 2087. Minimum Cost Homecoming of a Robot in a Grid
// https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/




class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int home_i = homePos[0];
        int home_j = homePos[1];

        int ans = 0;

        int i = startPos[0];
        while( i != home_i ) {
            if( i < home_i )
                ++i;
            else
                --i;
            ans += rowCosts[i];
        }

        int j = startPos[1];
        while( j != home_j ) {
            if( j < home_j )
                ++j;
            else
                --j;
            ans += colCosts[j];
        }

        return ans;
    }
};
