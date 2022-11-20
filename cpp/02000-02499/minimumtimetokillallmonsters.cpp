
// 2403. Minimum Time to Kill All Monsters
// https://leetcode.com/problems/minimum-time-to-kill-all-monsters/


class Solution {
private:
    int n;
    int end;
    int * pwr;

    long long mem[131072][18];
    // long long **mem;

    long long rec(int mask, int gain) {
        if( mask == end ) // all monsters are defeated
            return 0;

        if( mem[mask][gain] != -1 )
            return mem[mask][gain];

        long long ret = LLONG_MAX;

        for(int i = 0; i < n; ++i) {
            if( (mask >> i) & 1 ) // monster i already defeated
                continue;

            long long days = pwr[i] / gain;
            if( pwr[i] % gain != 0 )
                ++days;

            mask |= 1 << i;     // mark monster i as defeated
            days += rec(mask,gain+1);

            ret = min(ret,days);

            // backtrack
            mask &= ~(1 << i);
        }

        return mem[mask][gain] = ret;
    }


public:
    long long minimumTime(vector<int>& power) {
        n = power.size(); // 1 <= power.length <= 17
        if( n == 1 )
            return power[0];

        end = pow(2,n)-1;   // value of mask when all monsters are defeated

        // mem[mask][gain]
        // mem[2^n][n+1]
        // worst case 17 monsters
        // mem[131072][18];
        memset(mem,-1,sizeof mem);
        /*
        int np2 = end+1;
        mem = new long long *[np2];
        for(int i = 0; i < np2; ++i) {
            mem[i] = new long long[n+1];
            for(int j = 0; j < n+1; ++j)
                mem[i][j] = -1L;
        }
        */

        pwr = power.data();

        return rec(0,1);
    }
};
