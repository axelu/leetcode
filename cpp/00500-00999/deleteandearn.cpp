
// 740. Delete and Earn
// https://leetcode.com/problems/delete-and-earn/


class Solution {
private:
    int rec(vector<array<int,2>>& v, int n, int i, int mem[]) {
        if( i == n )
            return 0;

        if( i == n-1 )
            return v[i][0]*v[i][1];

        if( mem[i] != -1 )
            return mem[i];

        // if we get here, we know v[i][0] can be taken

        // we have a choice
        // take OR
        // leave

        // take
        int a = v[i][0]*v[i][1];
        a += v[i][0]+1 == v[i+1][0] ? rec(v,n,i+2,mem) : rec(v,n,i+1,mem);

        // leave
        int b = rec(v,n,i+1,mem);


        return mem[i] = max(a,b);
    }

public:
    int deleteAndEarn(vector<int>& nums) {
        int cnt[10001];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < nums.size(); ++i)
            ++cnt[nums[i]];

        // array to vector
        vector<array<int,2>> v;
        for(int i = 1; i < 10001; ++i)
            if( cnt[i] != 0 )
                v.push_back({i,cnt[i]});

        int n = v.size();

        // top down
        int mem[n];memset(mem,-1,sizeof mem);
        return rec(v,n,0,mem);

        /*
        // bottom up
        if( n == 1 )
            return v[0][0]*v[0][1];

        if( n == 2 ) {
            if( v[0][0]+1 == v[1][0] )
                return max(v[0][0]*v[0][1],v[1][0]*v[1][1]);
            else
                return v[0][0]*v[0][1] + v[1][0]*v[1][1];
        }

        int dp[n+1];
        dp[n] = 0;
        dp[n-1] = v[n-1][0]*v[n-1][1];
        for(int i = n-2; i >= 0; --i)
            dp[i] = v[i][0]+1 == v[i+1][0] ? max(v[i][0]*v[i][1] + dp[i+2],dp[i+1]) : v[i][0]*v[i][1] + dp[i+1];

        return dp[0];
        */
    }
};
