
// 3730. Maximum Calories Burnt from Jumps
// https://leetcode.com/problems/maximum-calories-burnt-from-jumps/



class Solution {
public:
    long long maxCaloriesBurnt(vector<int>& heights) {
        int n = heights.size();
        if( n == 1 )
            return (long long)heights[0] * (long long)heights[0];

        sort(begin(heights),end(heights), greater<int>());

        long long ans = (long long)heights[0] * (long long)heights[0];

        int i = 0;
        int j = n-1;
        while( i < j ) {
            // we are standing on i
            // jump to j
            long long diff = heights[i] - heights[j];
            ans += diff * diff;

            // now we are on j
            // advance i
            ++i;
            if( i == j )
                break;
            // jump to new i
            diff = heights[i] - heights[j];
            ans += diff * diff;
            // now we are on new i
            // advance j
            --j;
        }

        return ans;;
    }
};
