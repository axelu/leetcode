
// 2147. Number of Ways to Divide a Long Corridor
// https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/




class Solution {
public:
    int numberOfWays(string& corridor) {
        int n = corridor.size();

        // group into [start,end]
        vector<array<int,2>> v;
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if( corridor[i] == 'S' )
                if( cnt == 0 ) {
                    v.push_back({i,-1});
                    ++cnt;
                } else {
                    v.back()[1] = i;
                    cnt = 0;
                }

        if( v.empty() || v.back()[1] == -1 )
            return 0;

        long mod = 1000000007;
        long f = 1;
        for(int i = 1; i < v.size(); ++i)
            f = (f * (v[i][0] - v[i-1][1])) % mod;

        return f;
    }
};
