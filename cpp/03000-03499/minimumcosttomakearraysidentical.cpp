
// 3424. Minimum Cost to Make Arrays Identical
// https://leetcode.com/problems/minimum-cost-to-make-arrays-identical/




class Solution {
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        int n = arr.size(); //     1 <= arr.length == brr.length <= 1e5

        // baseline: don't split anywhere, just use operation b
        long long a = 0LL;
        for(int i = 0 ; i < n; ++i)
            a += (long long)abs(arr[i] - brr[i]);

        if( a == 0 )
            return 0;

        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        long long b = 0LL;
        for(int i = 0 ; i < n; ++i)
            b += (long long)abs(arr[i] - brr[i]);

        return min(a, b + k);
    }
};
