
// 1726. Tuple with Same Product
// https://leetcode.com/problems/tuple-with-same-product/


class Solution {
private:
    // Returns factorial of n
    long long fact(int n) {
        long long res = 1;
        for (int i = 2; i <= n; i++)
            res = res * (long long)i;
        return res;
    }

    int nPr(int n, int r) {
        return fact(n) / fact(n - r);
    }

public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        if( n < 4 )
            return 0;

        // a * b = c * d
        // because the integers in nums are distinct,
        // we know that if we find a product of two integers
        // more than once, that the factors are distinct
        // let a * b = A, let c * d = B =>
        //     A = B      ,      B = A
        // a * b = c * d     c * d = a * b
        // now in each we can change the order of a and b,
        // respectively c and d
        // more formaly, each permutation of 2 out of A, B, C, ...
        // with A = xi * xj, B = xk * xl, ... where A = B = C = ...
        // gives us 4 solutions
        // a*b=c*d, b*a=c*d, a*b=d*c, b*a=d*c

        unordered_map<int,int> um;
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                ++um[nums[i]*nums[j]];

        int ans = 0;

        for(auto it = um.begin(); it != um.end(); ++it) {
            int product_cnt = it->second;
            if( product_cnt > 1 )
                ans += nPr(product_cnt,2) * 4;
        }

        return ans;
    }
};
