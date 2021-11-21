
// 1986. Minimum Number of Work Sessions to Finish the Tasks
// https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/





class Solution {
private:
    int n;

    void printBinary(int x) {
        for(int i = n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int mem[16384][14];

    int rec(int mask, int session, int sessionTime, int times[]) {
        // cout << "rec mask ";printBinary(mask);cout << " session " << session << endl;

        // mask = bitmask of tasks taken so far

        if( mask == (1<<n)-1 ) // if all tasks are taken, no more session are needed
            return 0;

        // mask indicates tasks taken so far,
        // hence translate to all tasks we could take
        int taskstakable = ( (1<<n) - 1) ^ mask;

        if( mem[mask][session] != -1 )
            return mem[mask][session];

        int ret = 100000; // arbitrary

        // submask enumeration
        // https://cp-algorithms.com/algebra/all-submasks.html
        // "Given a bitmask m, you want to efficiently iterate through all of its submasks,
        //  that is, masks s in which only bits that were included in mask m are set."
        int s = taskstakable;
        int mask_new,myworkingtime;
        while(s > 0) {

            myworkingtime = times[s];
            if( myworkingtime <= sessionTime ) {
                mask_new = mask | s;
                ret = min(ret,rec(mask_new,session+1,sessionTime,times));
            }

            s = (s-1) & taskstakable;
        }

        return mem[mask][session] = 1 + ret;
    }

public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        n = tasks.size();   // 1 <= n <= 14

        // ans = n;            // worst case one task per session

        // precompute working times for any combination of tasks
        int times[1<<n];
        int workingTime;
        for(int i = 1; i < (1<<n); ++i) {
            workingTime = 0;
            for(int j = n-1; j >= 0; --j)
                if( i & (1 << j) )
                    workingTime += tasks[j];
            times[i] = workingTime;
        }

        // debug
        // for(int i = 1; i < (1<<n); ++i) {
        //     cout << "i " << i << " ";printBinary(i);cout << " " << times[i] << endl;
        // }


        memset(mem,-1,sizeof mem);
        return rec(0,0,sessionTime,times);
    }
};
