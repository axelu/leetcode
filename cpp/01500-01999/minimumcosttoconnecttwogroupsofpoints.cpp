
// 1595. Minimum Cost to Connect Two Groups of Points
// https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/



#include <iostream>
#include <cassert>
#include <chrono>
#include <bitset>

#include <vector>
#include <climits>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        m = cost.size();    // rows i (group 1)
        n = cost[0].size(); // columns j (group 2)

        // to check whether all points in group 2 are connected
        // set all n bits as 1
        g2allmask = (1 << n) - 1;

        // min for each group 2 point, basically min per column
        // used to connect the unconnected group 2 points
        g2min = vector<int>(n, INT_MAX);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                g2min[j] = min(g2min[j], cost[i][j]);

        // memory by mask of group 2
        // initializing an extra column (see m + 1) to hold the
        // cost of connecting the unconnected group 2 points
        dp = vector<vector<int>>(1 << n, vector<int>(m + 1, -1));

        return connect(0, 0, cost);
    }
private:
    int m;
    int n;
    // dp[n bits for group 2 mask][index of i'th element group 1 (+ group 2 unconnected)]
    vector<vector<int>> dp;
    int g2allmask;
    vector<int> g2min;


    int connect(int g2mask, int i, vector<vector<int>>& cost) {
        // cout << "g2mask " << bitset<12>(g2mask).to_string() << " i " << i << endl;

        // we already solved this problem
        if( dp[g2mask][i] != -1 ) return dp[g2mask][i];

        int r;

        if( i == m ) {
            // all points of group 1 are connected
            // collect and ultimately return the cost to connect
            // the unconnected (if any) points of group 2
            if( g2mask == g2allmask ) return 0; // all points of group 2 connected
            r = 0;
            for(int j = 0; j < n; ++j)
                if( (g2mask & (1<<j)) == 0 ) {
                    // j not connected
                    r += g2min[j];
                }
        } else {
            r = INT_MAX;
            for(int j = 0; j < n; ++j)
                // cost is basically the cost for connecting
                // i'th point of group 1 with the j'th point of group 2 ( = cost[i][j] ) PLUS
                // the cost of connecting (all) remaining i'th points ( i + 1 );
                // the g2mask communicates to downstream which j'th point of group 2 is already
                // connected, so that when all points of group 1 are connected, the cost to
                // connect the unconnected (if any) points of group 2 will be returned
                r = min(r, cost[i][j] + connect(g2mask|(1<<j), i + 1, cost) );
        }

        // save answer for future
        dp[g2mask][i] = r;

        return r;
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<vector<int>> cost;

    cost = {{1, 3, 5}, {4, 1, 1}, {1, 5, 3}}; // 4
    cout << s.connectTwoGroups(cost) << endl;


    return 0;
}

