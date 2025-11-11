
// 3738. Longest Non-Decreasing Subarray After Replacing at Most One Element
// https://leetcode.com/problems/longest-non-decreasing-subarray-after-replacing-at-most-one-element/




class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        if( n <= 2 )
            return n;

        // our min ans is 2
        // if nums is already non-decreasing, then n is our answer
        // otherwise there are 2 options
        //    we can merge 2 existing adjacent non-decreasing subarrays, more formally:
        //    let a and b be the start and end index of non-decreasing subarray with 0 <= a,b <= n-3
        //    let c and d be the start and end index of non-decreasing subarray with b+1 < c,d < n
        //    let nums[b] <= nums[c]
        //    then we can replace nums[b+1] with nums[b] to create non-decreasing subarray a..d
        //    OR
        //    we can extend an an existing non-decreasing subarray,
        //    we would choose the longest one

        int longest = 0; // length of longest non-decreasing subarray
        int longest_start = -1;
        int longest_end = -1;
        // pairs of start/end index of non-decreasing subarrays with length > 1
        vector<pair<int,int>> v;
        int s = 0;
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] > nums[i] ) {
                // index i-1 is potentially the end
                // of a non-decreasing subarray with length > 1
                int length = i - s;
                if( length > 1 ) {
                    v.push_back({s, i-1});
                    if( length > longest ) {
                        longest = length;
                        longest_start = s;
                        longest_end = i-1;
                    }
                }
                s = i;
            }
        }
        // finish up
        if( s < n-1 ) {
            int length = n - s;
            v.push_back({s, n-1});
            if( length > longest ) {
                longest = length;
                longest_start = s;
                longest_end = n-1;
            }
        }

        if( longest == 0 ) // nums is strictly decreasing
            return 2;

        // nums is already non decreasing
        if( longest_start == 0 && longest_end == n-1 )
            return n;

        int best = longest + 1;
        if( (longest_start == 0 && longest_end == n-2) ||
            (longest_start == 1 && longest_end == n-1) )
            return best;
        // we could also check instead
        // if( longest == n-1 )
        //     return best;

        int v_sz = v.size(); // v_sz >= 1
        if( v_sz == 1 )
            return best;

        for(int i = 1; i < v_sz; ++i) {
            int e = v[i-1].second;
            int s = v[i].first;
            if( e + 1 != s )
                continue;

            // there are two options
            //      x
            //    x   x
            //      e s decrease e to nums[s]
            // OR
            //    x   x
            //      x
            //    e s   increase s s to nums[e]

            if( nums[e-1] <= nums[s] || nums[e] <= nums[s+1] ) {
                int length = v[i].second - v[i-1].first + 1;
                best = max(best, length);
            }
        }

        return best;
    }
};
