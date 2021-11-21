
// 1723. Find Minimum Time to Finish All Jobs
// https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/


class Solution {
private:
    int n,K;
    
    void printBinary(int x) {
        for(int i = n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }
    
    int countSetBits(int x) {
        // 1 <= x <= 4095, 1 <= n <= 12
        int count = 0;
        for(int i = n-1; i >= 0; --i)
            if( x & (1 << i) ) 
                ++count;
        return count;
    }
    
    int mem[4096][13];
    int ans;
    
    int rec(vector<int>& jobs, int mask, int worker, int times[]) {
        // cout << "rec mask ";printBinary(mask);cout << " worker " << worker << endl;
        // mask = bitmask of jobs taken so far
        // jobs    0 indexed
        // workers 1 indexed

        
        // mask indicates jobs taken, 
        // hence translate to all jobs we could take
        int jobstakable = ( (1<<n) - 1) ^ mask;
        
        
        // if we are at the last worker, 
        // we have to take all remaining jobs
        if( worker == K )
            return times[jobstakable];
        
        
        if( mem[mask][worker] != -1 ) 
           return mem[mask][worker];
        

        int ret = INT_MAX;
        
        
        // submask enumeration
        // https://cp-algorithms.com/algebra/all-submasks.html
        // "Given a bitmask m, you want to efficiently iterate through all of its submasks, 
        //  that is, masks s in which only bits that were included in mask m are set."
        int s = jobstakable;
        int mask_new,myworkingtime,t,othersworkingtime;
        while(s > 0) {

            // leave enough jobs for the remaining workers
            // numberjobs - setbits >= numberworkers - currentworker
            if( n - countSetBits(s) >= K - worker ) {

                
                myworkingtime = times[s];
                if( myworkingtime >= ans )
                   continue;
                            
                mask_new = mask | s;
                othersworkingtime = rec(jobs,mask_new,worker+1,times);
                
                t = max(myworkingtime,othersworkingtime);
                ret = min(ret,t);
                if( worker == 0 )
                   ans = ret;
            }
            
            s = (s-1) & jobstakable;
        }

       
        return mem[mask][worker] = ret;
        //return ret;
    }

public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        if( k == 1 )
            return accumulate(begin(jobs),end(jobs),0);

        n = jobs.size();
        if( k == n )
            return *max_element(begin(jobs),end(jobs));
        
        
        // precompute working times for any combination of jobs
        int times[1<<n];
        int workingTime;
        for(int i = 1; i < (1<<n); ++i) {
            workingTime = 0;
            for(int j = n-1; j >= 0; --j)
                if( i & (1 << j) ) 
                    workingTime += jobs[j];
            times[i] = workingTime;
        }
        
        // debug
        // for(int i = 1; i < (1<<n); ++i)
        //     cout << "i " << i << " ";printBinary(i);cout << " " << times[i] << endl;
        

        K = k;
        memset(mem,-1,sizeof mem);
        ans = INT_MAX;
        return rec(jobs,0,1,times);
    }
};


