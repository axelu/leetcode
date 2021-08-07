
// 1335. Minimum Difficulty of a Job Schedule
// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/




class Solution {
private:
    
    int mem[300][11];
    
    int rec(vector<int>& jobDifficulty, int n, int pos, int rd) {
        // rd = remaining days
        
        if( mem[pos][rd] != -1 )
            return mem[pos][rd];
        
        
        if( rd == 1 ) {
            // all remaining jobs need to be finished
            int mx = 0;
            for(int i = pos; i < n; ++i)
                mx = max(mx,jobDifficulty[i]);
            return mx;
        }
        
        
        // we have a choice
        //    do one or more jobs today, but leave enough jobs
        //    for the days after today
        
        int ret = INT_MAX;
        
        int mx = 0; // max job difficulty of job done today
        for(int i = pos; i <= n - rd; ++i) {
            
            mx = max(mx,jobDifficulty[i]);
            ret = min(ret,mx+rec(jobDifficulty,n,i+1,rd-1));
            
        }
        
        return mem[pos][rd] = ret;
    }
    

public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        
        if( n < d )
            return -1;
        
        if( n == d )
            return accumulate(jobDifficulty.begin(),jobDifficulty.end(),0);

        
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= d; ++j)
                mem[i][j] = -1;
        
        return rec(jobDifficulty,n,0,d);
    }
};
