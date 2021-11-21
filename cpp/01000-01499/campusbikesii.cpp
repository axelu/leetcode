
// 1066. Campus Bikes II
// https://leetcode.com/problems/campus-bikes-ii/





class Solution {
private:
    void printBinary(int x, int m) {
        for(int i = m; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }


    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int manhattan(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    int mem[10][1024];

    int rec(vector<vector<int>>& bikes, int m, int j, vector<vector<int>>& workers, int n, int& mask) {
        // all bikes assigned?
        if( j == m )
            return 0;

        // all workers assigned?
        if( pow(2,n)-1 == mask )
           return 0;

        if( mem[j][mask] != -1 )
           return mem[j][mask];

        int ret = INT_MAX;

        // we have a choice
        // assign the current bike to a free worker
        int dist,t;
        for(int i = 0; i < n; ++i) {
            if( !((mask >> i) & 1U) ) {
                mask |= 1U << i;
                dist = manhattan(workers[i][0],workers[i][1],bikes[j][0],bikes[j][1]);
                t = dist + rec(bikes,m,j+1,workers,n,mask);
                ret = min(ret,t);
                // backtrack
                mask &= ~(1U << i);
            }
        }

        return mem[j][mask] = ret;
    }

    int rec2(vector<vector<int>>& bikes, int lb, int j, int bikesInPlay,
             vector<vector<int>>& workers, int n, int& mask) {

        if( j == lb ) {
            // assign the last bike to the remaining free worker
            for(int i = 0; i < n; ++i) {
                if( !((mask >> i) & 1U) ) {
                    return manhattan(workers[i][0],workers[i][1],bikes[j][0],bikes[j][1]);
                }
            }
        }

        if( mem[j][mask] != -1 )
           return mem[j][mask];

        // next bike
        int nb = j+1;
        for(; nb <= lb; ++nb)
            if( (bikesInPlay >> nb) & 1U )
                break;

        int ret = INT_MAX;

        // we have a choice
        // assign the current bike to a free worker
        int dist,t;
        for(int i = 0; i < n; ++i) {
            if( !((mask >> i) & 1U) ) {
                mask |= 1U << i;
                dist = manhattan(workers[i][0],workers[i][1],bikes[j][0],bikes[j][1]);
                t = dist + rec2(bikes,lb,nb,bikesInPlay,workers,n,mask);
                ret = min(ret,t);
                // backtrack
                mask &= ~(1U << i);
            }
        }

        return mem[j][mask] = ret;
    }

public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size();
        int m = bikes.size();   // 1 <= n <= m <= 10


        int mask = 0;           // no worker assigned

        // we can assign n out of m bikes
        /*
        if( n == m ) {
            memset(mem,-1,sizeof mem);
            return rec(bikes,m,0,workers,n,mask);
        }
        */

        int ans = INT_MAX;
        for(int k = 1; k < pow(2,m); ++k) {
            if( countSetBits(k) != n )
                continue;

            // k is the mask of the bikes in play
            // first bike in play (from right)
            int fb = 0;
            for(; fb < m; ++fb)
                if( (k >> fb) & 1U )
                    break;
            // last bike in play (from left)
            int lb = m-1;
            for(; lb >= n; --lb)
                if( (k >> lb) & 1U )
                    break;

            memset(mem,-1,sizeof mem);
            ans = min(ans,rec2(bikes,lb,fb,k,workers,n,mask));
        }

        return ans;
    }
};
