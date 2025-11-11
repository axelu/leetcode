
// 3679. Minimum Discards to Balance Inventory
// https://leetcode.com/problems/minimum-discards-to-balance-inventory/



class Solution {
public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        // 1 <= arrivals.length <= 1e5
        // 1 <= arrivals[i] <= 1e5
        // 1 <= w <= arrivals.length
        // 1 <= m <= w

        int n = arrivals.size(); // cout << "n " << n << endl;


        // TODO
        // edge cases
        // w = 1 -> m = 1
        // m = 1
        // w = n

        int cnt[100001]; memset(cnt, 0, sizeof cnt);

        int discards = 0;
        // track days on which we discarded an item
        bool discarded[100000]; memset(discarded, false, sizeof discarded);

        // sliding window
        int i = 0;
        for(int j = 0; j < n; ++j) {
            if( cnt[arrivals[j]] + 1 > m ) {
                ++discards;
                discarded[j] = true;
            } else {
                ++cnt[arrivals[j]];
            }

            /*
            cout << "j " << j << endl;
            for(int k = 1; k <= 10; ++k) // adjust k initial and k max to test case
                cout << k << ":" << cnt[k] << " ";
            cout << endl;
            */

            if( j-i+1 == w ) {
                if( !discarded[i] )
                    --cnt[arrivals[i]];
                ++i;
            }
        }

        return discards;
    }
};
