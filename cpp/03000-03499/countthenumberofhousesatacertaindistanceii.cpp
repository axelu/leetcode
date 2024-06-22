
// 3017. Count the Number of Houses at a Certain Distance II
// https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/







// see 3015. Count the Number of Houses at a Certain Distance I
// https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/
class Solution {
public:
    vector<long long> countOfPairs(int n, int x, int y) {
        // preconstruct our answer
        vector<long long> ans(n);
        long long _x = ((long long)n-1LL) * 2LL;
        for(int i = 0; i < n; ++i, _x -= 2LL)
            ans[i] = _x;

        if( x == y )
            return ans;

        if( x > y )
            swap(x, y);

        if( y - x == 1 )
            return ans;


        // for(int i = 0; i < n; ++i)
        //     cout << i << ":" << ans[i] << " ";
        // cout << endl;

        vector<long long> ls(n+1, 0LL);
        int l = y - x;              // cout << "l " << l << endl;
        int disty2last  = n - y;    // cout << "disty2last " << disty2last << endl;
        int distx2first = x - 1;    // cout << "distx2first " << distx2first << endl;
        // x                 y
        // *  *  *  *  *  *  *
        //   +1 +2 +3 +4 +5 +6   -->
        //         +4 +3 +2 +1   <--
        //            --------
        // there is a threshold of savings to elements inside x--y
        int t = (l - 1) / 2;
        if( (l - 1) % 2 )
            ++t;

        for(int k = 0; k < n; ++k) {

            int i = k + 1; // 1 indexed
            int disti2first = i - 1;
            int disti2last  = n - i;

            if( i <= x ) {
                int disti2x     = x - i;
                int disti2y     = y - i;
                // cout << "i " << i << " disti2x " << disti2x << " disti2y " << disti2y << " disti2last " << disti2last << endl;
                // cout << " shorten the way to y and everything right of y from i" << endl;
                --ls[disti2y - 1];                  // cout << "  --" << disti2y - 1 << endl;
                ++ls[disti2last];                   // cout << "  ++" << disti2last << endl;
                ++ls[disti2x];                      // cout << "  ++" << disti2x << endl;
                --ls[disti2x + (disty2last + 1)];   // cout << "  --" << disti2x + (disty2last + 1) << endl;
                // cout << " shorten the way to elements inside x--y" << endl;
                int d = disti2y - (disti2x + 1);
                if( d > 2 ) {
                    int range = d / 2;
                    if( d % 2 == 0 )
                        --range;

                    --ls[disti2y - range - 1];      // cout << "  --" << disti2y - range - 1 << endl;
                    ++ls[disti2y - 1];              // cout << "  ++" << disti2y - 1 << endl;
                    ++ls[disti2x + 1];              // cout << "  ++" << disti2x + 1 << endl;
                    --ls[disti2x + 1 + range];      // cout << "  --" << disti2x + 1 + range << endl;
                }

            } else if( i > x && i < y ) {

                int disti2x     = i - x;
                int disti2y     = y - i;
                if( disti2x > disti2y + 1 ) {
                    // it is faster to get to x going forward to y and then using our new road to go from y to x
                    // shorten the way to x and everything left of x
                    --ls[disti2x - 1];                   // cout << "  --" << disti2x - 1 << endl;
                    ++ls[disti2first];                   // cout << "  ++" << disti2first << endl;
                    ++ls[disti2y];                       // cout << "  ++" << disti2y << endl;
                    --ls[disti2y + (distx2first + 1)];   // cout << "  --" << disti2y + (distx2first + 1) << endl;
                    // shorten the way to elements inside x--y
                    int d = disti2x - (disti2y + 1);
                    if( d > 2 ) {
                        int range = d / 2;
                        if( d % 2 == 0 )
                            --range;

                        --ls[disti2x - range - 1];
                        ++ls[disti2x - 1];
                        ++ls[disti2y + 1];
                        --ls[disti2y + 1 + range];
                    }

                } else if( disti2y > disti2x + 1 ) {
                    // it is faster to get to y going back to x and then using our new road to go from x to y
                    // shorten the way to y and everything to the right of y
                    --ls[disti2y - 1];                  // cout << "  --" << disti2y - 1 << endl;
                    ++ls[disti2last];                   // cout << "  ++" << disti2last << endl;
                    ++ls[disti2x];                      // cout << "  ++" << disti2x << endl;
                    --ls[disti2x + (disty2last + 1)];   // cout << "  --" << disti2x + (disty2last + 1) << endl;
                    // shorten the way to elements inside x--y
                    int d = disti2y - (disti2x + 1);
                    if( d > 2 ) {
                        int range = d / 2;
                        if( d % 2 == 0 )
                            --range;

                        --ls[disti2y - range - 1];
                        ++ls[disti2y - 1];
                        ++ls[disti2x + 1];
                        --ls[disti2x + 1 + range];
                    }
                }

            } else { // i >= y
                int disti2x     = i - x;
                int disti2y     = i - y;
                // cout << "i " << i << " disti2x " << disti2x << " disti2y " << disti2y << " disti2first " << disti2first << endl;
                // shorten the way to x and everything left of x from i;
                --ls[disti2x - 1];                   // cout << "  --" << disti2x - 1 << endl;
                ++ls[disti2first];                   // cout << "  ++" << disti2first << endl;
                ++ls[disti2y];                       // cout << "  ++" << disti2y << endl;
                --ls[disti2y + (distx2first + 1)];   // cout << "  --" << disti2y + (distx2first + 1) << endl;
                // shorten the way to elements inside x--y
                int d = disti2x - (disti2y + 1);
                if( d > 2 ) {
                    int range = d / 2;
                    if( d % 2 == 0 )
                        --range;

                    --ls[disti2x - range - 1];
                    ++ls[disti2x - 1];
                    ++ls[disti2y + 1];
                    --ls[disti2y + 1 + range];
                }
            }
        }

        // line sweep
        long long diff = 0LL;
        for(int i = 0; i < n; ++i) {
            diff += ls[i];
            ans[i] += diff;
        }


        return ans;
    }
};
