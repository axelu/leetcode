
// 3376. Minimum Time to Break Locks I
// https://leetcode.com/problems/minimum-time-to-break-locks-i/




class Solution {
private:
    int mem[256][81];

    int rec(vector<int>& strength, int n, int K, int state, int X) {
        // strength is sorted
        // state represents which locks are still to be broken

        // if state == 0, all locks are broken -> return 0
        if( state == 0 )
            return 0;

        if( mem[state][X] != -1 )
            return mem[state][X];

        // we will wait here till we can break
        // an unbroken lock, we go there and keep track of min time required

        int ret = INT_MAX;

        for(int i = 0; i < n; ++i) {
            if( state & (1<<i) ) {

                // every minute our energy gross by X
                int t = strength[i] / X;
                if( (strength[i] %  X) != 0 )
                    ++t;

                int state_new = state & ~(1 << i);
                ret = min(ret, t + rec(strength, n, K, state_new, X + K));
            }
        }

        return mem[state][X] = ret;
    }



public:
    int findMinimumTime(vector<int>& strength, int K) {
        int n = strength.size(); // 1 <= n <= 8

        memset(mem,-1,sizeof mem);
        return rec(strength, n, K, pow(2,n)-1, 1);
    }
};
