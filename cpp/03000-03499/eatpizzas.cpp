

// 3457. Eat Pizzas!
// https://leetcode.com/problems/eat-pizzas/





class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        int n = pizzas.size();
        long long ans = 0LL;

        // n is divisible by 4
        // 1-indexed !!!
        // let k = n / 4
        // if k is odd, then we have div/2 + 1 odd, and div/2 even
        // if k is even, then we have div/2 odd and div/2 even

        // we grab the odd largest pizzas, and then jump by 2 for the even ones

        sort(begin(pizzas),end(pizzas));
        int k = n / 4;
        int odd = k / 2;
        if( k % 2 )
            ++odd;

        for(int i = n-1; i >= n-odd; --i, --k)
            ans += (long long)pizzas[i];


        for(int i = n-odd-2; k > 0; i -= 2, --k)
            ans += (long long)pizzas[i];

        return ans;
    }
};
