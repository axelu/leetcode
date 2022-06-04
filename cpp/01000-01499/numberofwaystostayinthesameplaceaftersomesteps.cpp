
// 1269. Number of Ways to Stay in the Same Place After Some Steps
// https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/



/*
 * arrLen: we can only ever go as far as idx steps/2 (0-indexed).
 * example: steps = 7   7/2 = 3
 * array idx0: step1 -> idx1: step2 -> idx2: step3 -> idx3
 * now we need to get back
 * so our memory is min(steps/2, arrLen)
*/
class Solution {
private:
    long mod = 1000000007;
    long mem[251][501];

    long rec(int mx, int idx, int rem) {
        // cout << "rec idx " << idx << " rem " << rem << endl;

        if( rem == 0 && idx != 0 )
            return 0;

        if( rem == 0 && idx == 0 )
            return 1;

        if( mem[idx][rem] != -1 )
            return mem[idx][rem];

        // we have a choice
        //    go right
        //    go left
        //    stay


        long ret = 0;

        int t = rem;
        while( t > 0 ) {
            if( idx < mx ) {
                long a = rec(mx,idx+1,t-1);
                if( a > 0 )
                    ret = (ret + a) % mod;;
            }

            if( idx > 0 ) {
                long b = rec(mx,idx-1,t-1);
                if( b > 0 )
                    ret = (ret + b) % mod;

            }

            --t;
        }

        if( idx == 0 )
            ++ret;

        // cout << "rec idx " << idx << " rem " << rem << " return " << ret << endl;
        return mem[idx][rem] = ret % mod;
    }

public:
    int numWays(int steps, int arrLen) {
        int mx = min(steps/2,arrLen-1);
        // cout << "mx " << mx << endl;

        memset(mem,-1,sizeof mem);

        return rec(mx,0,steps);
    }
};
