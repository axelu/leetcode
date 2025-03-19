
// 2529. Maximum Count of Positive Integer and Negative Integer
// https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/

class Solution {
public:
    int maximumCount(vector<int>& nums) {
        // nums is sorted in non-decreasing order
        
        int n = nums.size();

        if( n == 1 ) {
            return nums[0] == 0 ? 0 : 1;
        }
        
        
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int target = 0;
        int s = 0;
        int e = n; // n = nums.size()
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

        if( s == 0 )            // we only have positive numbers
            return n;

        if( s == n ) {
            if( nums[n-1] < 0 ) // we only have negative numbers
                return n;
        }
        
        int pos = n-s;
        
        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        e = s+1;
        s = 0;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && nums[s] >= target) || s == n )
            --s;

        int neg = s+1;
        
        return max(pos,neg);
    }
};
