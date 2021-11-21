
// 1846. Maximum Element After Decreasing and Rearranging
// https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/




class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return 1;

        sort(begin(arr),end(arr));
        arr[0] = 1;

        int ans = 1;
        int diff;

        for(int i = 1; i < n; ++i) {

            diff = arr[i]-arr[i-1];
            if( diff > 1 )
                arr[i] = arr[i-1]+1;
            ans = max(ans,arr[i]);
        }

        return ans;
    }
};
