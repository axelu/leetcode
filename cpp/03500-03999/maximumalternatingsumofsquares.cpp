
// 3727. Maximum Alternating Sum of Squares
// https://leetcode.com/problems/maximum-alternating-sum-of-squares/



class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        // we want the largest absolute values on even indices
        sort(begin(nums), end(nums), [](int a, int b){
            return a*a > b*b;
        });

        // number of even indices
        int evens = n / 2;
        if( n % 2 )
            ++evens;

        long long ans = 0LL;

        int i = 0;
        for(; i < evens; ++i)
            ans += (long long)nums[i] * nums[i];
        for(; i < n; ++i)
            ans -= (long long)nums[i] * nums[i];

        return ans;
    }
};
