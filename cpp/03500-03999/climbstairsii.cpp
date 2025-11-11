
// 3693. Climbing Stairs II
// https://leetcode.com/problems/climbing-stairs-ii/



class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // 1 <= n == costs.lenfth <= 1e5; costs is 1-indexed

        int i, j;
        deque<int> dq;
        dq.push_front(0);
        int cost, mn_cost;
        for(i = n-1; i >= 0; --i) {
            // from step i we have a choice
            //    jump to step j=i+1
            //    jump to step j=i+2 (if j <= n)
            //    jump to step j=i+3 (if j <= n)

            j = i+1;
            cost = costs[j-1] + (j-i)*(j-i);
            mn_cost = cost + dq[0];

            j = i+2;
            if( j <= n ) {
                cost = costs[j-1] + (j-i)*(j-i);
                mn_cost = min(mn_cost, cost + dq[1]);
            }

            j = i+3;
            if( j <= n ) {
                cost = costs[j-1] + (j-i)*(j-i);
                mn_cost = min(mn_cost, cost + dq[2]);
            }

            if( dq.size() == 3 )
                dq.pop_back();

            dq.push_front(mn_cost);
        }

        return mn_cost;
    }
};
