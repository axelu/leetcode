
// 1478. Allocate Mailboxes
// https://leetcode.com/problems/allocate-mailboxes/




// see also
// https://leetcode.com/problems/best-meeting-point/
// https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/

class Solution {
private:
    int mem[100][101];

    int rec(vector<int>& houses, int n, int s, int k) {
        if( n-s == k ) // each house gets its own mailbox
            return 0;

        if( k == 1 ) { // place the one and only mailbox at the median
            int mid = s + (((n-1)-s)/2);
            int med = houses[mid];
            int ret = 0;
            for(int i = s; i < n; ++i)
                ret += abs(med-houses[i]);
            return ret;
        }

        if( mem[s][k] != -1 )
            return mem[s][k];

        // we have a choice
        // place a mailbox at the current house OR
        // place a mailbox at the median of the next houses
        int a = rec(houses,n,s+1,k-1);

        int b = INT_MAX;
        for(int i = s+1; i < n; ++i) {
            if( n-(i+1) < k-1 )
                break;

            int mid = s + ((i-s)/2);
            int med = houses[mid];
            int t = 0;
            for(int j = s; j <= i; ++j)
                t += abs(med-houses[j]);

            b = min(b,t+rec(houses,n,i+1,k-1));
        }

        return mem[s][k] = min(a,b);
    }

public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();

        sort(begin(houses),end(houses));
        memset(mem,-1,sizeof mem);
        return rec(houses,n,0,k);
    }
};
