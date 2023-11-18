
// 2831. Find the Longest Equal Subarray
// https://leetcode.com/problems/find-the-longest-equal-subarray/




class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> indicies[n+1];
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            indicies[x].push_back(i);
        }

        int ans = 0;

        // 1 <= nums[i] <= nums.length
        for(int x = 1; x <= n; ++x) {

            // sliding window
            int i = 0;                                    // left index
            for(int j = 0; j < indicies[x].size(); ++j) { // right index
                // distance between indicies in window
                int di = indicies[x][j] - indicies[x][i] + 1;
                // number of indicies in window
                int ni = j - i + 1;
                // number of indicies in window where nums[index] != x
                int t = di - ni;

                // shrink the window if needed
                while( t > k ) {
                    ++i;
                    di = indicies[x][j] - indicies[x][i] + 1;
                    ni = j - i + 1;
                    t = di - ni;
                }
                ans = max(ans, ni);
            }
        }

        return ans;
    }
};
