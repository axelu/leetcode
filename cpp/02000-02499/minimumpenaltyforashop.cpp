
// 2483. Minimum Penalty for a Shop
// https://leetcode.com/problems/minimum-penalty-for-a-shop/



class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();

        // examples
        // 0123
        // YYYY  -> close at hour 4, as there is a customer every hour
        // NNNN  -> close at hour 0, as there are no customers ever
        // YYNY  -> close at hour 2 penalty 1

        // counting Y's will give baseline if we would close
        // the shop at hour 0, meaning don't open at all
        int base = 0;
        for(int i = 0; i < n; ++i)
            if( customers[i] == 'Y' )
                ++i;

        int mn_penalty = base;
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            // if we would be closed at hour i and there is a customer
            // we have a penalty

            if( customers[i-1] == 'Y' )
                --base;
            else
                ++base;

            if( base < mn_penalty ) {
                mn_penalty = base;
                ans = i;
            }

        }

        return ans;
    }
};
