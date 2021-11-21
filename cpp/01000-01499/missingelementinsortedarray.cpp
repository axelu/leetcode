
// 1060. Missing Element in Sorted Array
// https://leetcode.com/problems/missing-element-in-sorted-array/



class Solution {
private:
    // binary search
    int search(vector<int>& nums, int s, int e, int k) {
        // returns rightmost index where
        // missing(index-1) < k <= missing(index)

        if( s > e )
            return -1;

        if( s == e )
            return s;

        int mid = s + ((e-s)/2);
        int missing = nums[mid] - nums[0] - mid; // count of missing numbers
        if( k > missing ) {
            // can we do better?
            int t = search(nums,mid+1,e,k);
            return t != -1 ? t : mid;
        } else {
            return search(nums,s,mid,k);
        }
    }


public:
    int missingElement(vector<int>& nums, int k) {
        int n = nums.size();

        // example
        // 0  1  2  3  4 n=5
        // 4  6  7 10 11
        // there should be a total of 8 numbers from 4 to 11
        // but we only have 5, so there are 3 numbers missing
        int missing = nums[n-1] - nums[0] - (n-1);

        // if k is greater than than the count of misssing numbers,
        // then the kth missing number is greater then nums[n-1]
        if( k > missing )
            return nums[n-1] - missing + k;



        int t = search(nums,0,n-1,k);
        missing = nums[t-1] - nums[0] - (t-1);
        return nums[t-1] - missing + k;
    }
};
