
// 2431. Maximize Total Tastiness of Purchased Fruits
// https://leetcode.com/problems/maximize-total-tastiness-of-purchased-fruits/



class Solution {
private:
    int N;
    int * _price;
    int * _tastiness;

    int seen[100][1001][6];

    int rec(int i, int amount, int coupons) {
        if( i == N )
            return 0;

        if( seen[i][amount][coupons] != -1 )
            return seen[i][amount][coupons];

        // at each index we have a choice:
        //     - skip the current fruit
        //     - buy the current fruit w/o a coupon (if we have enough money)
        //     - buy the current fruit w/ a coupon (if we have a coupon and enough money)

        int a = rec(i+1,amount,coupons);

        int b = 0;
        if( amount >= _price[i] )
            b = _tastiness[i] + rec(i+1,amount-_price[i],coupons);

        int c = 0;
        if( coupons > 0 && amount >= _price[i]/2 )
            c = _tastiness[i] + rec(i+1,amount-_price[i]/2,coupons-1);

        return seen[i][amount][coupons] = max({a,b,c});
    }

public:
    int maxTastiness(vector<int>& price, vector<int>& tastiness, int maxAmount, int maxCoupons) {
        N = price.size(); // price.length == tastiness.length

        _price = price.data();
        _tastiness = tastiness.data();
        memset(seen,-1,sizeof seen);

        return rec(0,maxAmount,maxCoupons);
    }
};
