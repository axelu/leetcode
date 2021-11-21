
// 153. Find Minimum in Rotated Sorted Array
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/



class Solution {
private:
    // binary search min in rotated sorted array with unique values
    int search(vector<int>& nums, int n, int s, int e) {
        // returns index of min element

        int mid = s+((e-s)/2);

        if( nums[mid] < nums[n-1] ) {
            int l = mid == 0 ? -5001 : nums[mid-1];
            if( l > nums[mid] ) return mid;
            return search(nums,n,s,mid-1);
        }
        return search(nums,n,mid+1,e);
    }
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();

        if( n == 1 ) return nums[0];
        if( n == 2 ) return nums[0] < nums[1] ? nums[0] : nums[1];
        if( n == 3 ) {
            if( nums[0] < nums[1] && nums[0] < nums[2] ) {
                return nums[0];
            } else if( nums[1] < nums[0] && nums[1] < nums[2] ) {
                return nums[1];
            } else {
                return nums[2];
            }
        }

        if( nums[0]   > nums[1]   ) return nums[1];   // rotated 1 time
        if( nums[0]   < nums[n-1] ) return nums[0];   // already sorted
        if( nums[n-2] > nums[n-1] ) return nums[n-1]; // rotate n-1 times

        return nums[search(nums,n,0,n-1)];
    }
};
