
// 1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
// https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/




class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();

        int ans = 0;
        double sum = 0.0, avg;
        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << endl;
            if( i < k ) {
                sum += arr[i];
                if( i == k-1 ) {
                    avg = sum/(double)k;
                    // cout << "avg " << avg << endl;
                    if( avg-(double)threshold >= 0.0 ) ++ans;
                }
                continue;
            }
            sum += arr[i];
            sum -= arr[i-k];
            avg = sum/(double)k;
            // cout << "avg " << avg << endl;
            if( avg-(double)threshold >= 0.0 ) ++ans;
        }

        return ans;
    }
};
