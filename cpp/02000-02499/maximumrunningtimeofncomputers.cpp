
// 2141. Maximum Running Time of N Computers
// https://leetcode.com/problems/maximum-running-time-of-n-computers/



class Solution {
private:

    // binary search
    int search(int s, int e, int n, int batteries_sz, long long prefixSum[]) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        int div = n - (batteries_sz - (mid+1));
        if( div <= 0 )
            return search(mid+1,e,n,batteries_sz,prefixSum);

        long long sum = prefixSum[mid+1];
        long long avg = sum/div;
        if( (prefixSum[mid+1]-prefixSum[mid]) > avg ) {
            return search(s,mid-1,n,batteries_sz,prefixSum);
        } else {
            // can we do better?
            int t = search(mid+1,e,n,batteries_sz,prefixSum);
            return t != -1 ? t : mid;
        }
    }

public:
    long long maxRunTime(int n, vector<int>& batteries) {
        int batteries_sz = batteries.size();
        if( n == batteries_sz )
            return *min_element(batteries.begin(),batteries.end());

        sort(batteries.begin(),batteries.end());

        // long long sum = accumulate(batteries.begin(),batteries.end(),0LL);
        long long prefixSum[batteries_sz+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= batteries_sz; ++i)
            prefixSum[i] = prefixSum[i-1] + batteries[i-1];

        long long sum = prefixSum[batteries_sz];
        if( n == 1 )
            return sum;

        // our answer is somewhere between the smallest battery and
        // our ability to distribute the entire power (read: sum) equally
        // between all computers aka average = sum/n;

        // our batteries are now sorted ascending
        // if we go from right (most powerful battery) to left (least power battery):
        //   - if the current battery can give more power to single computer than
        //   the power that could be equally distributed to all of the computers (read: average),
        //   then the current battery can run a single computer all the time, and our
        //   problem reduces itself to the remaining batteries and remaining computers.
        //   - if however the current battery does not have more power then the average, then
        //   the answer is our average.

        /*
        // brute force
        long long avg = sum/n;
        for(int i = batteries_sz - 1;i >= 0; --i)
           if( batteries[i] > avg ) {
               sum -= batteries[i];
               // avg = sum/(n - (batteries_sz - i));
               avg = sum/--n;
           } else {
               break;
           }

        return avg;
        */

        // binary search
        int i = search(0,batteries_sz-1,n,batteries_sz,prefixSum);
        return prefixSum[i+1]/(n - (batteries_sz - (i+1)));
    }
};
