
// 540. Single Element in a Sorted Array
// https://leetcode.com/problems/single-element-in-a-sorted-array/



class Solution {
private:
    // binary search
    int search(vector<int>& nums, int n, int s, int e) {
        // cout << "search s " << s << " e " << e << endl;

        int mid = s + ((e-s)/2);
        // cout << "  mid " << mid << endl;

        if( mid == 0 || mid == n-1 )
            return mid;

        if( nums[mid-1] != nums[mid] && nums[mid] != nums[mid+1] )
            return mid;

        if( mid % 2 == 0 ) {
            if( nums[mid-1] == nums[mid] )
                return search(nums,n,s,mid-1);
            else
                return search(nums,n,mid+1,e);
        } else {
             if( nums[mid-1] != nums[mid] )
                return search(nums,n,s,mid-1);
            else
                return search(nums,n,mid+1,e);
        }
    }

public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];


        return nums[search(nums,n,0,n-1)];
    }
};
