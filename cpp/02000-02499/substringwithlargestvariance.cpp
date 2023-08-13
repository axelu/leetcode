
// 2272. Substring With Largest Variance
// https://leetcode.com/problems/substring-with-largest-variance/





// after solutions approach
class Solution {
public:
    int largestVariance(string s) {
        // Kadane's Algorithm, but modified
        // Kadane's algorithm is a dynamic programming algorithm,
        // that finds the maximum subarray sum in an array of integers.
        // It maintains two values:
        //    global_max, which represents the maximum sum encountered so far, and
        //    local_max, which represents the maximum sum ending at the current index.
        // As the algorithm traverses the array from left to right, it updates these values.
        // https://en.wikipedia.org/wiki/Maximum_subarray_problem

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c : s)
            ++cnt[c - 'a'];

        int globalMax = 0;
        // we will check every possible pair of characters
        for(int i = 0; i < 26; ++i) {       // our char a
            for(int j = 0; j < 26; ++j) {   // our char b
                // char pair must be different chars AND
                // we must have either char in s
                if( i == j || cnt[i] == 0 || cnt[j] == 0 )
                    continue;

                // we need to find the maximum variance of a_cnt - b_cnt.
                char a = 'a' + i;
                int a_cnt = 0;
                char b = 'a' + j;
                int b_cnt = 0;

                int b_remaining = cnt[j];

                for(char c : s) {
                    if( c == a ) {
                        ++a_cnt;
                    }
                    if( c == b ) {
                        ++b_cnt;
                        --b_remaining;
                    }

                    // only update the variance (local_max) if there is at least one char b
                    if( b_cnt > 0 )
                        globalMax = max(globalMax, a_cnt - b_cnt);

                    // discard the previous string if there is at least one remaining minor
                    if( a_cnt < b_cnt && b_remaining > 0) {
                        a_cnt = 0;
                        b_cnt = 0;
                    }
                }
            }
        }

        return globalMax;
    }
};
