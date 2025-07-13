
// 3562. Maximum Profit from Trading Stocks with Discounts
// https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/




// Knapsack Problem
// https://algocademy.com/blog/understanding-the-knapsack-problem-and-solutions/
// https://cp-algorithms.com/dynamic_programming/knapsack.html


class Solution {
private:
    vector<int> t[160]; // n-ary tree rooted in node 0


    // memory pos budget buy/not buy
    // nodes max 160, budget max 160, buy/not buy 2
    // 160 161 2
    int mem[160][161][2];

    void rec(vector<int>& present, vector<int>& future, int u, int mx_budget) {

        // calculate max profit after each child and for each possible budget (0 <= budget <= mx_budget)
        int pre[161][2];
        memset(pre,0,sizeof(int) * 161 * 2);
        int cur[161][2];
        memset(cur,0,sizeof(int) * 161 * 2);

        for(int v: t[u]) {
            rec(present, future, v, mx_budget);

            for(int budget = 0; budget <= mx_budget; ++budget) {
                // split the budget between the children so far and the current child !!!
                for(int child_budget = budget; child_budget >= 0; --child_budget) {

                    cur[budget][0] = max(cur[budget][0], pre[budget - child_budget][0] + mem[v][child_budget][0]);
                    cur[budget][1] = max(cur[budget][1], pre[budget - child_budget][1] + mem[v][child_budget][1]);
                }
            }

            swap(pre, cur);
        }

        int cost = present[u];
        int half_cost = cost / 2; // floor as int division
        int gain = future[u];

        // we have a choice
        //    don't buy OR
        //    buy if we can
        for(int budget = 0; budget <= mx_budget; ++budget) {
            // full price
            mem[u][budget][0] = pre[budget][0]; // don't buy
            if( budget >= cost )                // buy if we can
                mem[u][budget][0] = max(mem[u][budget][0], gain - cost + pre[budget - cost][1]);

            // half price
            mem[u][budget][1] = pre[budget][0]; // don't buy
            if( budget >= half_cost )           // buy if we can
                mem[u][budget][1] = max(mem[u][budget][1], gain - half_cost + pre[budget - half_cost][1]);
        }

        return;
    }


public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        for(auto& p: hierarchy) {
            int u = p[0]-1; // boss aka parent node, 1-indexed to 0-indexed
            int v = p[1]-1; // employee aka child node, 1-indexed to 0-indexed
            t[u].push_back(v);
        }

        memset(mem,0,sizeof mem);
        rec(present, future, 0, budget);

        // CEO node 0, with budget, and full price (as she doesn't have a boss)
        // that is our answer
        return mem[0][budget][0];
    }
};
