
// 3065. Minimum Operations to Exceed Threshold Value I
// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/




class Solution {
private:
     int lower_bound(vector<int>& nums, int target) {
         int n = nums.size();

        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
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

public:
    int minOperations(vector<int>& nums, int k) {
        // it is guaranteed that there is at least one index i such that nums[i] >= k
        sort(nums.begin(), nums.end());
        return lower_bound(nums, k);
    }
};
