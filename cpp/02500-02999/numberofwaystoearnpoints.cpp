
// 2585. Number of Ways to Earn Points
// https://leetcode.com/problems/number-of-ways-to-earn-points/





class Solution {
private:
    long mod = 1000000007;
    long mem[51][1001];

    long rec(vector<vector<int>>& types, int n, int pos, int target) {
        // cout << "rec i " << i << " k " << k << endl;
        if( target == 0 )
            return 1L;
        if( pos == n )
            return 0L;

        if( mem[pos][target] != -1 )
            return mem[pos][target];

        // we have a choice
        //    skip the current question OR
        //    answer 1 or more question of the current type

        long ret = rec(types,n,pos+1,target);
        int k = target;
        for(int i = 0; i < types[pos][0]; ++i) {
            k -= types[pos][1];
            if( k < 0 )
                break;
            ret = (ret + rec(types,n,pos+1,k)) % mod;
        }

        return mem[pos][target] = ret;
    }

public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        memset(mem,-1,sizeof mem);
        return rec(types,types.size(),0,target);
    }
};
