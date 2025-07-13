
// 3535. Unit Conversion II
// https://leetcode.com/problems/unit-conversion-ii/





class Solution {
private:
    const long mod = 1000000007;

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


    vector<int> conversion_factors_base;

    void rec(vector<vector<vector<int>>>& t, int u, long f) {
        conversion_factors_base[u] = (int)f;

        int n = t[u].size();
        for(int i = 0; i < n; ++i) {
            int v = t[u][i][0];
            if( conversion_factors_base[v] != -1 )
                continue;

            long weight = t[u][i][1];
            rec(t, v, (f * weight) % mod);
        }

        return;
    }

public:
    vector<int> queryConversions(vector<vector<int>>& conversions, vector<vector<int>>& queries) {
        // TODO consider precalculating modInverse 1 - 1000000006

        // step 1 identical to 3528. Unit Conversion I https://leetcode.com/problems/unit-conversion-i/
        //    we record all conversion factors from the base unit to any other unit

        // weighted undirected tree rooted at 0

        int n = conversions.size() + 1;

        vector<vector<vector<int>>> t(n,vector<vector<int>>());
        for(auto& conversion: conversions) {
            int u  = conversion[0];     // sourceUnit
            int v = conversion[1];      // targetUnit
            int weight = conversion[2]; // conversionFactor

            t[u].push_back({v,weight});
            t[v].push_back({u,weight});
        }

        conversion_factors_base.assign(n,-1);
        rec(t, 0, 1L);

        // step 2 process queries
        //            root
        //              |
        //             ...
        //              |
        //            unitC LCA
        //            /   \
        //          ...   ...
        //          /       \
        //        unitA    unitB
        // we know conversion factors: root_unitA and root_unitB
        // so we can calculate going from unitA to root = inverse(root_unitA)
        // and then from root to unitB = root_unitB

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int A = queries[i][0];
            long root_A = (long)conversion_factors_base[A];

            int B = queries[i][1];
            long root_B = (long)conversion_factors_base[B];

            ans[i] = (modInverse(root_A) * root_B) % mod;
        }

        return ans;
    }
};
