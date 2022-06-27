
// 1473. Paint House III
// https://leetcode.com/problems/paint-house-iii/



class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // dp[i][j][k] min cost where we have k neighborhoods in the first i houses and
        //             the i-th house is painted with the color j

        // m number of houses 1 <= m <= 100
        // n number of colors 1 <= n <= 20
        // 1 <= target <= m

        int dp[m][n][m+1];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                for(int k = 1; k <= m; ++k)
                    dp[i][j][k] = 1000001;

        // 1st house ( house[0] ), it starts the 1st neighborhood
        if( houses[0] == 0 )
            // house 0 is not painted -> paint it any color
            for(int j = 0; j < n; ++j)
                dp[0][j][1] = cost[0][j];
        else
            dp[0][houses[0]-1][1] = 0;

        int k_min = 1; // min neighborhoods
        int k_max = 1; // max neighborhoods

        // for each house starting at house 1
        for(int i = 1; i < m; ++i) {
            // cout << "at house i " << i << endl;

            // cases:
            // case 1 prior house: painted     current house: painted
            // case 2 prior house: painted     current house: not painted
            // case 3 prior house: not painted current house: painted
            // case 4 prior house: not painted current house: not painted

            // case 1 prior house: painted     current house: painted
            if( houses[i-1] != 0 && houses[i] != 0 ) {
                // we have no new cost

                // if color of current house is the same color as prior house
                //     no new neighborhood is started
                // if color of current house is a different color as prior house
                //     a new neighborhood is started

                if( houses[i] == houses[i-1] ) {
                    // for each possible number of neighborhoods
                    for(int k = k_min; k <= min({i,k_max,target}); ++k)
                        dp[i][houses[i]-1][k] = dp[i-1][houses[i-1]-1][k];
                } else {
                    // for each possible number of neighborhoods
                    ++k_max;
                    for(int k = k_min + 1; k <= min({i+1,k_max,target}); ++k)
                        dp[i][houses[i]-1][k] = dp[i-1][houses[i-1]-1][k-1];
                    ++k_min;
                    if( k_min > target )
                        break;
                }

            // case 2 prior house: painted     current house: not painted
            } else if( houses[i-1] != 0 && houses[i] == 0 ) {
                // we have cost of painting the current house

                // if we paint the current house the same color as prior house
                //     no new neighborhood is started
                // if we paint the current house a different color as prior house
                //     a new neighborhood is started

                // paint current house with same color as prior house
                // for each possible number of neighborhoods
                for(int k = k_min; k <= min({i,k_max,target}); ++k)
                    dp[i][houses[i-1]-1][k] = dp[i-1][houses[i-1]-1][k] + cost[i][houses[i-1]-1];

                // paint current house with a color different than prior house
                ++k_max;
                for(int j = 0; j < n; ++j) {
                    if( j == houses[i-1]-1 )
                        continue;
                    // for each possible number of neighborhoods
                    for(int k = k_min+1; k <= min({i+1,k_max,target}); ++k)
                        dp[i][j][k] = min(dp[i][j][k],dp[i-1][houses[i-1]-1][k-1] + cost[i][j]);
                }

            // case 3 prior house: not painted current house: painted
            } else if( houses[i-1] == 0 && houses[i] != 0 ) {
                // we have no new cost

                // check when prior house has the same color
                // for each possible number of neighborhoods
                for(int k = k_min; k <= min({i,k_max,target}); ++k)
                    dp[i][houses[i]-1][k] = dp[i-1][houses[i]-1][k];

                // for each possible number of neighborhoods
                ++k_max;
                for(int k = k_min+1; k <= min({i+1,k_max,target}); ++k) {
                    // for each color that the prior house could be painted in
                    // different than the color of the current house
                    int t = 1000001;
                    for(int j = 0; j < n; ++j) {
                        if( j == houses[i]-1 )
                            continue;

                        t = min(t,dp[i-1][j][k-1]);
                    }
                    dp[i][houses[i]-1][k] = min(dp[i][houses[i]-1][k],t);
                }

            // case 4 prior house: not painted current house: not painted
            } else { // houses[i-1] == 0 && houses[i] == 0
                // we have cost of painting the current house

                // pass 1
                // paint current house the same color as the prior house
                // for each possible number of neighborhoods
                for(int k = k_min; k <= min({i,k_max,target}); ++k)
                    // for each possible color
                    for(int j = 0; j < n; ++j)
                        dp[i][j][k] = dp[i-1][j][k] + cost[i][j];

                // pass 2
                // paint the current house a color different than the prior house
                // for each possible number of neighborhoods
                ++k_max;
                for(int k = k_min+1; k <= min({i+1,k_max,target}); ++k)
                    // for each possible color
                    for(int j = 0; j < n; ++j)
                        for(int j_pre = 0; j_pre < n; ++j_pre) {
                            if( j_pre == j )
                                continue;
                            dp[i][j][k] = min(dp[i][j][k],dp[i-1][j_pre][k-1] + cost[i][j]);
                        }

            }
        }

        if( k_min > target || k_max < target )
            return -1;

        if( houses[m-1] != 0 )
            return dp[m-1][houses[m-1]-1][target] != 1000001 ? dp[m-1][houses[m-1]-1][target] : -1;

        int ans = 1000001;
        for(int j = 0; j < n; ++j)
            ans = min(ans,dp[m-1][j][target]);
        return ans;
    }
};
