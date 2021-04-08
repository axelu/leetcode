
// 1508. Range Sum of Sorted Subarray Sums
// https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/


class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int l = n*(n+1)/2;
        int arr[l];
        int s, k = 0;
        for(int i = 0; i < n; ++i) {
            s = 0;
            for(int j = i; j < n; ++j) {
                s += nums[j];
                arr[k] = s;
                ++k;
            }
        }
        sort(arr,arr+l);
        s = 0;
        int mod = 1000000007;
        for(int i = left-1; i <= right-1; ++i) {
            s = (s+(arr[i]%mod))%mod;
        }
        return s;
    }
};
