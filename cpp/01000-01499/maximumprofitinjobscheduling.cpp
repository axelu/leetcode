
// 1235. Maximum Profit in Job Scheduling
// https://leetcode.com/problems/maximum-profit-in-job-scheduling/
// day 28 August 2021 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3950/



class Solution {
private:
    int n;

    // binary search equal or greater aka lower bound
    int search(vector<array<int,3>>& arr, int s, int e, int x) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid][0] >= x ) {
            // can we do better?
            int t = search(arr,s,mid-1,x);
            return t != -1 ? t : mid;
        } else {
            return search(arr,mid+1,e,x);
        }
    }

    int rec(vector<array<int,3>>& stm, int pos, int mem[]) {
        // cout << "rec pos " << pos << endl;
        if( pos == n )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];


        // we have a choice
        // take the job at the current position and then take the next possible job OR
        // skip the job at the current position and take the next job


        // take the job at the current position
        int a = stm[pos][2];
        // can we take another job?
        int next = search(stm,pos+1,n-1,stm[pos][1]);
        if( next != -1 )
            a += rec(stm,next,mem);


        // skip the current job
        int b = rec(stm,pos+1,mem);


        return mem[pos] = max(a,b);
    }

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        // 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
        n = startTime.size();

        vector<array<int,3>> stm(n); // startTime,endTime,profit
        for(int i = 0; i < n; ++i)
            stm[i] = {startTime[i],endTime[i],profit[i]};
        sort(stm.begin(),stm.end());

        int mem[n];memset(mem,-1,sizeof mem);
        return rec(stm,0,mem);
    }
};
