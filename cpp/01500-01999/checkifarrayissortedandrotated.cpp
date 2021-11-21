
// 1752. Check if Array Is Sorted and Rotated
// https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/


class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 100
        if( n == 1 ) return true;

        // An array A rotated by x positions results in an array B
        // of the same length such that A[i] == B[(i+x) % A.length].

        int x = -1,i;
        for(i = 1; i < n; ++i)
            if( nums[i-1] > nums[i] ) {
                x = i;
                break;
            }
        if( x == -1 ) return true; // array already sorted

        for(i = 1; i < n; ++i)
            if( nums[(i-1+x)%n] > nums[(i+x)%n] ) return false;
        return true;
    }
};
