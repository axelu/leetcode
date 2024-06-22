
// 2801. Count Stepping Numbers in Range
// https://leetcode.com/problems/count-stepping-numbers-in-range/





class Solution {
private:
    const long mod = 1000000007;

    long mem[100][2][2][10];

    long rec(string& low, string& high, int posh, int le, int he, int digit) {
        // cout << "rec posh " << posh << " le " << le << " he " << he << " digit " << digit << endl;

        // if we arive at pos with digit, it has been validated that this is possible
        // pos is the position in high, we are lining high and low up at their ends
        int n_hi = high.size();
        if( posh == n_hi - 1 )
            return 1L;

        if( mem[posh][le][he][digit] != -1L )
            return mem[posh][le][he][digit];

        int n_lo = low.size();
        int posl = posh - (n_hi - n_lo);

        int lo_nxt;
        if( posl >= 0 )
            lo_nxt = low[posl+1] - '0';
        int hi_nxt = high[posh+1] - '0';

        long ret = 0L;

        if( le && !he ) {
            // moving along the low edge
            // down
            if( digit > 0 ) {
                if( lo_nxt < digit - 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 0, digit - 1)) % mod;
                } else if( lo_nxt == digit -1 ) {
                    ret = (ret + rec(low, high, posh + 1, 1, 0, digit - 1)) % mod;
                }
            }
            // up
            if( digit < 9 ) {
                if( lo_nxt < digit + 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 0, digit + 1)) % mod;
                } else if( lo_nxt == digit + 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 1, 0, digit + 1)) % mod;
                }
            }

        } else if( !le && he ) {
            // moving along the high edge
            // down
            if( digit > 0 ) {
                if( hi_nxt > digit - 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 0, digit - 1)) % mod;
                } else if( hi_nxt == digit -1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 1, digit - 1)) % mod;
                }
            }
            // up
            if( digit < 9 ) {
                if( hi_nxt > digit + 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 0, digit + 1)) % mod;
                } else if( hi_nxt == digit + 1 ) {
                    ret = (ret + rec(low, high, posh + 1, 0, 1, digit + 1)) % mod;
                }
            }

        } else if( !le && !he ) {
            // down
            if( digit > 0 )
                ret = (ret + rec(low, high, posh + 1, 0, 0, digit - 1)) % mod;
            // up
            if( digit < 9 )
                ret = (ret + rec(low, high, posh + 1, 0, 0, digit + 1)) % mod;

        } else { // le && he
            // moving along the low and high edge
            // down
            if( digit > 0 ) {
                if( lo_nxt < digit - 1 ) {
                    if( hi_nxt > digit - 1 )
                        ret = (ret + rec(low, high, posh + 1, 0, 0, digit - 1)) % mod;
                    else if( hi_nxt == digit - 1 )
                        ret = (ret + rec(low, high, posh + 1, 0, 1, digit - 1)) % mod;

                } else if( lo_nxt == digit - 1 ) {
                    if( hi_nxt > digit - 1 )
                        ret = (ret + rec(low, high, posh + 1, 1, 0, digit - 1)) % mod;
                    else if( hi_nxt == digit - 1 )
                        ret = (ret + rec(low, high, posh + 1, 1, 1, digit - 1)) % mod;
                }
            }
            // up
            if( digit < 9 ) {
                if( hi_nxt > digit + 1 ) {
                    if( lo_nxt < digit + 1 )
                        ret = (ret + rec(low, high, posh + 1, 0, 0, digit + 1)) % mod;
                    else if( lo_nxt == digit + 1 )
                        ret = (ret + rec(low, high, posh + 1, 1, 0, digit + 1)) % mod;
                } else if( hi_nxt == digit + 1 ) {
                     if( lo_nxt < digit + 1 )
                        ret = (ret + rec(low, high, posh + 1, 0, 1, digit + 1)) % mod;
                    else if( lo_nxt == digit + 1 )
                        ret = (ret + rec(low, high, posh + 1, 1, 1, digit + 1)) % mod;
                }
            }

        }

        return mem[posh][le][he][digit] = ret;
    }


public:
    int countSteppingNumbers(string low, string high) {
        int n_hi = high.size();
        int n_lo = low.size();
        int d = n_hi - n_lo;

        long ans = 0L;
        memset(mem,-1,sizeof mem);

        for(int i = d; i >= 0; --i) {
            if( i == d ) {
                if( i == 0 ) {
                    // low and high have the same length
                    int start = low[0] - '0';
                    int limit = high[0] - '0';
                    if( start == limit ) {
                        ans = (ans + rec(low, high, i, 1, 1, start)) % mod;
                    } else {
                        ans = (ans + rec(low, high, i, 1, 0, start)) % mod;
                        for(int k = start + 1; k < limit; ++k)
                            ans = (ans + rec(low, high, i, 0, 0, k)) % mod;
                        ans = (ans + rec(low, high, i, 0, 1, limit)) % mod;
                    }

                } else {
                    // high is longer than low
                    int start = low[0] - '0';
                    ans = (ans + rec(low, high, i, 1, 0, start)) % mod;
                    for(int k = start + 1; k <= 9; ++k)
                        ans = (ans + rec(low, high, i, 0, 0, k)) % mod;
                }

            } else if( i == 0 ) {
                int limit = high[0] - '0';
                for(int k = 1; k < limit; ++k)
                    ans = (ans + rec(low, high, i, 0, 0, k)) % mod;

                ans = (ans + rec(low, high, i, 0, 1, limit)) % mod;

            } else {
                // A stepping number should not have a leading zero.
                for(int k = 1; k <= 9; ++k)
                    ans = (ans + rec(low, high, i, 0, 0, k)) % mod;
            }
        }

        return ans;
    }
};
