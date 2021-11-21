
// 1493. Longest Subarray of 1's After Deleting One Element
// https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/




class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        // leading and trailing zero's can be ignored
        int k = 0;
        for(; k < n; ++k)
            if( nums[k] == 1 )
                break;
        if( k == n )
            return 0;

        int i = k; // left idx
        int j = k; // right idx
        k = n-1;
        for(; k >= 0; --k)
            if( nums[k] == 1 )
                break;

        if( k == i )
            return 1;

        // sliding window
        int zeros = 0;
        int ans = 0;
        int idxLastZero,l;
        for(j = i+1; j < k+1; ++j) {

            if( nums[j] == 0 ) {
                if( zeros == 0 ) {
                    idxLastZero = j;
                    ++zeros;
                } else {
                    l = j-1-i;
                    ans = max(ans,l);
                    // advance i aka left idx to last idx of last '0' + 1
                    i = idxLastZero+1;
                    idxLastZero = j;
                }
            }
        }
        // finish up
        if( zeros == 0 )
            return i > 0 || j < n ? j-i : j-i-1;

        l = j-1-i;
        return max(ans,l);
    }
};
