
// 2920. Maximum Points After Collecting Coins From All Nodes
// https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/

class Solution {
private:
    int mem[100000][14];
    
    int dfs(vector<int> g[], int u, vector<int>& coins, int k, bool seen[], int way2) {
        // cout << "dfs u " << u << " way2 " << way2 << endl;
        
        // 0 <= coins[i] <= 10000
        // decimal 10000 -> binary 10011100010000 (14 digits)
        // because dividing by 2 and flooring is the same as bit shifting to the right
        // if way2 >= 14, then we can stop as us and the subtree will return 0
        if( way2 >= 14 )
            return 0;

        if( mem[u][way2] != -1 )
            return mem[u][way2];
        
        seen[u] = true;
        
        // we have a choice
        //    continue way 1 getting coins[i] - k after adjusting coins[i] based on how often 
        //    our ancestors used way 2 already
        //    OR
        //    continue way 2 getting floor(coins[i] / 2)
        
        int base = coins[u];
        // dividing by 2 and flooring is the same as bit shifting to the right
        for(int k = 0; k < way2 && base > 0; ++k)
            base >>= 1;
        
        int a = base - k;
        int b = base / 2;
        
        for(auto v: g[u]) {
            if( !seen[v] ) {
                a += dfs(g,v,coins,k,seen,way2);
                b += dfs(g,v,coins,k,seen,way2+1);
            }
        }
        
        seen[u] = false; // because we will come back with another option
        return mem[u][way2] = max(a,b);
    }
    
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        if( k == 0 )
            return accumulate(coins.begin(),coins.end(),0);

        int n = edges.size();
        
        vector<int> g[n+1]; // undirected tree rooted at node 0
        for(auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        
        memset(mem,-1,sizeof mem);
        bool seen[n+1];memset(seen,false,sizeof seen);
        return dfs(g,0,coins,k,seen,0);
    }
};



