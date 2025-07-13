
// 3528. Unit Conversion I
// https://leetcode.com/problems/unit-conversion-i/




class Solution {
private:
    const long mod = 1000000007;

    vector<int> ans;

    void rec(vector<vector<vector<int>>>& t, int u, long f) {
        ans[u] = (int)f;

        int n = t[u].size();
        for(int i = 0; i < n; ++i) {
            int v = t[u][i][0];
            if( ans[v] != -1 )
                continue;

            long weight = t[u][i][1];
            rec(t, v, (f * weight) % mod);
        }

        return;
    }

public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
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

        ans.assign(n,-1);
        rec(t, 0, 1L);

        return ans;
    }
};
