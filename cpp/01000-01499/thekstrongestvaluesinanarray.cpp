
// 1471. The k Strongest Values in an Array
// https://leetcode.com/problems/the-k-strongest-values-in-an-array/


class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        // arr[i] is stronger arr[j] if
        // |arr[i] - m| > |arr[j] - m| where m is the median of the array

        int n = arr.size();

        // brute force

        sort(arr.begin(),arr.end());

        int median_idx = (n-1)/2;
        int m = arr[median_idx]; // cout << "median " << m << endl;

        vector<array<int,2>> v(n); // abs(nums[i]-m),nums[i]
        for(int i = 0; i < n; ++i)
            v[i] = {abs(arr[i]-m),arr[i]};
        sort(v.begin(),v.end(),[](const array<int,2>& a, const array<int,2>& b){
            if( a[0] > b[0] ) {
               return true;
            } else if( a[0] == b[0] ) {
               if( a[1] > b[1] ) {
                   return true;
               }
            }
            return false;
        });

        vector<int> ans(k);
        for(int i = 0; i < k; ++i) {
            ans[i] = v[i][1];
        }

        return ans;
    }
};
