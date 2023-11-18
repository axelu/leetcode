
// 2742. Painting the Walls
// https://leetcode.com/problems/painting-the-walls/




class Solution {
private:
    int mem[500][500];

    int rec(vector<int>& cost, vector<int>& time, int n, int wall, int walls_painted) {
        if( walls_painted >= n )
            return 0;
        if( wall == n )
            return 1000000000;

        if( mem[wall][walls_painted] != -1 )
            return mem[wall][walls_painted];

        // we have a choice
        //    the paid painter does not paint the current wall OR
        //    the paid painter paints the current wall

        int a = rec(cost, time, n, wall + 1, walls_painted);

        // while the paid painter paints the current wall (+1),
        // the free painter paints time[wall] walls
        int b = cost[wall] + rec(cost, time, n, wall + 1, walls_painted + 1 + time[wall]);

        return mem[wall][walls_painted] = min(a,b);
    }

public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size(); // cost.size() == time.size()

        // the free painter can paint any wall in 1 unit of time
        // so the paid painter only needs to work n/2 units of time

        memset(mem,-1,sizeof mem);
        return rec(cost,time,n,0,0);
    }
};
