
// 1916. Count Ways to Build Rooms in an Ant Colony
// https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/



class Solution {
private:
    //   calculate number of combinations MOD 10^9+7
    //   https://barkingbogart.wordpress.com/2013/02/21/cnk-mod-1000000007/

    long mod = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    /*
    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%mod;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %mod;

        long long res = modInverse(denominator);
        res = (res*numerator)%mod;
        return res;
    }
    */

    long * factorial;
    long * inverse;

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

    void dfs(vector<int> g[], int u, long nbr_nodes[], long dp[]){
        // lazy initialization
        nbr_nodes[u] = 0L;
        dp[u] = 1L;

        for(int v : g[u]) {
            dfs(g,v,nbr_nodes,dp);
            dp[u] = (dp[u] * dp[v]) % mod;
            nbr_nodes[u] += nbr_nodes[v];
        }

        // number of combinations
        int nodes = nbr_nodes[u];
        for(int v : g[u]) {
            dp[u] = (dp[u] * modCombinations(nodes,nbr_nodes[v])) % mod;
            nodes -= nbr_nodes[v];
        }

        ++nbr_nodes[u]; // add current node
    }

public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        int n = prevRoom.size();

        // number of ways for a given node
        // example node with 2 children
        // ways[child0] * ways[child1] * nCr(nbr_nodes[child0] + nbr_nodes[child1], nbr_nodes[child0])

        // precompute
        long _factorial[n+1]; factorial = _factorial;
        factorial[0] = 1L;
        long _inverse[n+1]; inverse = _inverse;
        inverse[0] = 1L;
        for(long i = 1; i <= n; ++i) {
            factorial[i] = (factorial[i-1] * i) % mod;
            inverse[i]   = modInverse(factorial[i]);
        }

        vector<int> g[n]; // directed graph
        for(int i = 1 ; i < n ; ++i)
            g[prevRoom[i]].push_back(i);

        long nbr_nodes[n]; // nbr nodes subtree rooted at i (including i)
        long dp[n];        // answer for node i
        dfs(g,0,nbr_nodes,dp);
        return dp[0];
    }

};
