
// 2221. Find Triangular Sum of an Array
// https://leetcode.com/problems/find-triangular-sum-of-an-array/



class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];

        int * a = nums.data();
        vector<int> B(n-1);
        int * b = B.data();

        while( n > 1 ) {
            for(int i = 1; i < n; ++i)
                b[i-1] = (a[i-1] + a[i]) % 10;
            int * t = a;
            a = b;
            b = t;
            --n;
        }

        return a[0];
    }
};
