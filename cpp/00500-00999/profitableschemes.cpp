
// 879. Profitable Schemes
// https://leetcode.com/problems/profitable-schemes/


class Solution {
private:
    long mod = 1000000007;
    int mem[101][101][100];

    long rec(vector<int>& group,
             vector<int>& profit,
             int rem_profit,
             int rem_members,
             int i)
    {
        if( rem_members == 0 )
            return 0;
        if( i == profit.size() ) // group.size == profit.size
            return 0;

        if( mem[rem_profit][rem_members][i] != -1 )
            return mem[rem_profit][rem_members][i];

        // we have a choice:
        //      commit crime i (if we have enough team members) OR
        //      don't commit crime i

        long a = 0;
        if( rem_members >= group[i] ) {     // do we have enough members to commit this crime?
            int p = rem_profit - profit[i]; // did we make enough profit just by doing this one?
            if( p <= 0 )
                a = 1 + rec(group,profit,0,rem_members-group[i],i+1);
            else
                a = rec(group,profit,p,rem_members-group[i],i+1);
        }

        long b = rec(group,profit,rem_profit,rem_members,i+1);

        return mem[rem_profit][rem_members][i] = (a + b) % mod;
    }

public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {

        memset(mem,-1,sizeof mem);
        int t = rec(group,profit,minProfit,n,0);
        // if no profit is required at all,
        // then there is one more choice: don't commit any crime
        return minProfit == 0 ? t + 1 : t;
    }
};
