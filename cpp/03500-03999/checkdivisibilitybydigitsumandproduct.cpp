
// 3622. Check Divisibility by Digit Sum and Product
// https://leetcode.com/problems/check-divisibility-by-digit-sum-and-product/



class Solution {
public:
    bool checkDivisibility(int n) {

        int x = n;
        int digit_sum = 0;
        int digit_product = 1;
        while(x) {
            int rem = x % 10;
            digit_sum += rem;
            digit_product *= rem;
            x /= 10;
        }

        return n % (digit_sum + digit_product) == 0;
    }
};
