
// 2806. Account Balance After Rounded Purchase
// https://leetcode.com/problems/account-balance-after-rounded-purchase/



class Solution {
public:
    int accountBalanceAfterPurchase(int purchaseAmount) {
        int t = purchaseAmount / 10;

        int a = t * 10;
        int b = (t+1) * 10;

        if( abs(a-purchaseAmount) < abs(b-purchaseAmount) )
            return 100 - a;
        else
            return 100 -b;
    }
};
