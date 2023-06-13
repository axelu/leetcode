
// 2706. Buy Two Chocolates
// https://leetcode.com/problems/buy-two-chocolates/




class Solution {
public:
    int buyChoco(vector<int>& prices, int money) {
        sort(prices.begin(),prices.end());
        
        int purchase = prices[0] + prices[1];
        
        int leftover = money - purchase;
        
        return leftover >= 0 ? leftover : money;
    }
};
