
// 1672. Richest Customer Wealth
// https://leetcode.com/problems/richest-customer-wealth/


class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int r = 0;

        size_t m = accounts.size();
        for(int i = 0; i < m; ++i)
            r = max(r,accumulate(begin(accounts[i]),end(accounts[i]),0));

        return r;
    }
};
