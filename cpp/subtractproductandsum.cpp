
// 1281. Subtract the Product and Sum of Digits of an Integer
// https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/


class Solution {
public:
    int subtractProductAndSum(int n) {
        int prd = 1;
        int sum = 0;

        while( n > 0 ) {
            int rem = n % 10;
            prd *= rem;
            sum += rem;
            n /= 10;
        }

        return prd - sum;
    }
};
