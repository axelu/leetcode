
// 746. Min Cost Climbing Stairs
// https://leetcode.com/problems/min-cost-climbing-stairs/



class Solution {
private:
    int mem[1000];

    int minCost(vector<int>& cost, int i, int n) {
        if( i >= n ) return 0;

        if( mem[i] != -1 ) return mem[i];

        return mem[i] = cost[i] + min(minCost(cost,i+1,n),minCost(cost,i+2,n));
    }

public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size(); // 2 <= n <= 1000
        for(int i = 0; i < n; ++i) mem[i] = -1;

        return min(minCost(cost,0,n),minCost(cost,1,n));
    }
};
