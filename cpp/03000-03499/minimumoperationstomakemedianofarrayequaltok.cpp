
// 3107. Minimum Operations to Make Median of Array Equal to K
// https://leetcode.com/problems/minimum-operations-to-make-median-of-array-equal-to-k/






class Solution {
private:

    // binary search lower bound
    int lower_bound(vector<int>& nums, int s, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  s  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    // binary search upper bound
    int upper_bound(vector<int>& nums, int s, int e, int target) {
        int n = e;

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        // int s = 0;
        // int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        // definition of Median for this problem (!!!):
        // The median of an array is defined as the middle element of the array
        // when it is sorted in non-decreasing order. If there are two choices
        // for a median, the larger of the two values is taken.
        // example [1,2,2,4,5,6] -> median is 4 (normally it would be (2 + 4)/2 = 3)

        int n = nums.size();
        if( n == 1 )
            return (long long)abs(nums[0] - k);

        sort(nums.begin(),nums.end());

        int median_idx = n / 2; // cout << "median_idx " << median_idx << endl;
        if( nums[median_idx] == k )
            return 0LL;

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

        if( nums[median_idx] < k ) {
            // let j be the index of the 1st element where nums[j]>= k with median_idx < j < n;
            // increase all elements [median_idx+1,j-1] to k
            int j = lower_bound(nums, median_idx + 1, n, k);
            int l = j - median_idx;
            return ((long long)l * (long long)k) - (prefixSum[j] - prefixSum[median_idx]);

        } else { // nums[median_idx] > k
            // let j be the index of the 1st element where nums[j] > k with 0 <= j < median_idx
            // decrease all element [j,median_idx] to k
            int j = upper_bound(nums, 0, median_idx, k);    // cout << "j " << j << endl;
            int l = median_idx - j + 1;                     // cout << "l " << l << endl;
            return  (prefixSum[median_idx + 1] - prefixSum[j])  - ((long long)l * (long long)k);
        }
    }
};
