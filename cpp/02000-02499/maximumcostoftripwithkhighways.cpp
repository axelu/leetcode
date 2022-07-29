
// 2247. Maximum Cost of Trip With K Highways
// https://leetcode.com/problems/maximum-cost-of-trip-with-k-highways/




class Solution {
private:
    // debug
    void printBinary(int x) {
        int n = 15;
        for(int i = n-1; i >= 0; --i) {
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

    int mem[32768][15]; // bitmask cities visited, city being visited

    int rec(vector<array<int,2>> g[], int u, int state, int k) {
        // cout << "rec u " << u << " src " << " state ";printBinary(state);cout << endl;
        // if state is 0, then we have not visited any city
        // in other words: we are just starting out

        int set_bits = countSetBits(state);
        if( set_bits == k )
            return -3; // reach the end

        if( mem[state][u] != -2 )
            return mem[state][u];

        // mark current city as visited
        state ^= 1 << u;

        int ret = -1;
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i][0];
            if( !((state >> v) & 1) ) {
                int t = rec(g,v,state,k);
                if( t == -3 ) {
                    ret = max(ret,g[u][i][1]);
                } else if( t >= 0 ) {
                    ret = max(ret,g[u][i][1]+t);
                }
            }
        }

        // backtrack
        state &= ~(1 << u);

        return mem[state][u] = ret;
    }


public:
    int maximumCost(int n, vector<vector<int>>& highways, int k) {
        // 2 <= n <= 15

        // undirected graph
        vector<array<int,2>> g[n]; // adjacent city, toll
        for(auto& v : highways) {
            g[v[0]].push_back({v[1],v[2]});
            g[v[1]].push_back({v[0],v[2]});
        }

        int ans = -1;

        for(int i = 0; i < 32768; ++i)
            for(int j = 0; j < 15; ++j)
                mem[i][j] = -2;

        // memset(mem,-1,sizeof mem);
        for(int u = 0; u < n; ++u) {
            int t = rec(g,u,0,k);
            ans = max(ans,t);
        }

        return ans;
    }
};
