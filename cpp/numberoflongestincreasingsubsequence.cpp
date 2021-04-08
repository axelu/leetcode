

// 673. Number of Longest Increasing Subsequence
// https://leetcode.com/problems/number-of-longest-increasing-subsequence/


class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if( n <= 1 ) return n; // base case

        int lengths[n]; // lengths[i] = length of longest ending in nums[i]
        int counts[n];  // count[i] = number of longest ending in nums[i]
        for(int i = 0; i < n; ++i) {
            lengths[i] = 1;
            counts[i] = 1;
        }

        for(int j = 0; j < n; ++j) {
            for(int i = 0; i < j; ++i) {
                // cout << "j " << j << " " << " i " << i << endl;
                // cout << "lengths and counts before" << endl;
                // for(int k = 0; k < n; ++k) cout << lengths[k] << " ";
                // cout << endl;
                // for(int k = 0; k < n; ++k) cout << counts[k] << " ";
                // cout << endl;
                if( nums[i] < nums[j] ) {
                    if( lengths[i] >= lengths[j] ) {
                        lengths[j] = lengths[i] + 1;
                        counts[j] = counts[i];
                    } else if( lengths[i] + 1 == lengths[j] ) {
                        counts[j] += counts[i];
                    }
                }
                // cout << "lengths and counts after" << endl;
                // for(int k = 0; k < n; ++k) cout << lengths[k] << " ";
                // cout << endl;
                // for(int k = 0; k < n; ++k) cout << counts[k] << " ";
                // cout << endl;
            }
        }

        // get longest
        int longest = 0;
        for(int i = 0; i < n; ++i)
            longest = max(longest, lengths[i]);

        // get count of longest
        int r = 0;
        for(int i = 0; i < n; ++i)
            if(lengths[i] == longest)
                r += counts[i];

        return r;
    }
};
