
// 2420. Find All Good Indices
// https://leetcode.com/problems/find-all-good-indices/



/* e.g. nums = {2,1,1,2}, k = 2
 * ans = {};
 * Note that we look at indicies in range: k <= i < n-k
 *   so we would start at index 2, and end at index 1 -> n = 4, k = 2,
 *   so if i is supposed to be less than n-k -> 4-2 = 2 -> i < 2
 *   that gives us no valid index to begin with!
 */

class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();

        int s = k;
        int e = n-k-1;
        if( e < s )
            return {};

        vector<int> ans;

        // if k == 1, then the left window and right window will always be 'good'
        // then it just becomes a matter of the number of i in range [s,e] inclusive
        if( k == 1 ) {
            for(int i = s; i <= e; ++ i)
                ans.push_back(i);
            return ans;
        }

        // build the intial right window
        // right start = 1, right end = 0 + k - 1
        int rc = 0; // count of bad indicies in right window
        for(int i = 2; i <= k-1; ++i)
            if( nums[i] < nums[i-1] )
                ++rc;

        // sliding window on the left of i and the right of i
        int lc = 0; // count of bad indicies in left window
        for(int i = 0; i <= e; ++i) {

            // left window, we are adding nums[i-1]
            if( i > 1 && nums[i-1] > nums[i-2] )
                ++lc;

            // right window, we are adding nums[i+k]
            if( nums[i+k] < nums[i+k-1] )
                ++rc;

            if( i >= s && i <= e && lc == 0 && rc == 0 )
                ans.push_back(i);

            // left window, we are dropping nums[x] with x = max(0,i-k)
            if( i-k >= 0 && nums[i-k] < nums[i-k+1] )
                --lc;

            // right window, we are dropping nums[i+1]
            if( nums[i+1] > nums[i+2] )
                --rc;
        }

        return ans;
    }
};
