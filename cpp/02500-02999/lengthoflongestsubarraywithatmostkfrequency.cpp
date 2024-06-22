
// 2958. Length of Longest Subarray With at Most K Frequency
// https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/




class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();

        int ans = 0;

        // sliding window
        unordered_map<int,int> freq;
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index

            ++freq[nums[j]];
            if( freq[nums[j]] > k ) {

                // we need to decrease our window
                while( i <= j ) {
                    --freq[nums[i]];
                    if( nums[i] == nums[j] ) {
                        ++i;
                        break;
                    }
                    ++i;
                }
            }

            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};
