
// 2291. Maximum Profit From Trading Stocks
// https://leetcode.com/problems/maximum-profit-from-trading-stocks/




class Solution {
private:
    int n;
    int * _present;
    int * _future;

    int **mem;

    int rec(int i, int budget) {
        if( i == n )
            return 0;

        if( mem[i][budget] != -1 )
            return mem[i][budget];

        // at each stock we have a choice
        //     skip taking any of the current stock
        //     take 1 whereas k * present[i] <= budget
        //     Note: only if there is a profit in the future

        int ret = rec(i+1,budget);

        if( _present[i] < _future[i] && _present[i] <= budget )
            ret = max(ret,(_future[i]-_present[i]) + rec(i+1,budget-_present[i]));

        return mem[i][budget] = ret;
    }
public:
    int maximumProfit(vector<int>& present, vector<int>& future, int budget) {
        n = present.size(); // present.size() == future.size()
        _future = future.data();
        _present = present.data();

        mem = new int *[n];
        for(int i = 0; i < n; ++i) {
            mem[i] = new int[budget+1];
            for(int j = 0; j < budget+1; ++j)
                mem[i][j] = -1;
        }

        return rec(0,budget);
    }
};
