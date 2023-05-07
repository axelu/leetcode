
// 2107. Number of Unique Flavors After Sharing K Candies
// https://leetcode.com/problems/number-of-unique-flavors-after-sharing-k-candies/



class Solution {
public:
    int shareCandies(vector<int>& candies, int k) {

        unordered_map<int,int> us; // val,count
        for(int x: candies)
            ++us[x];

        if( k == 0 )
            return us.size();

        int ans = 0;

        // sliding window
        int n = candies.size();
        int i = 0;
        for(int j = 0; j < n; ++j) {
            --us[candies[j]];
            if( us[candies[j]] == 0 )
                us.erase(candies[j]);

            if( j - i + 1 == k ) {
                ans = max(ans,(int)us.size());
                ++us[candies[i]];
                ++i;
            }
        }

        return ans;
    }
};
