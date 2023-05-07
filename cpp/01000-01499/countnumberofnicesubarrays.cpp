
// 1248. Count Number of Nice Subarrays
// https://leetcode.com/problems/count-number-of-nice-subarrays/



class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        int ans = 0;

        // sliding window

        // we need to keep track of the left most odd number idx in the window
        // we need to keep track of the right most odd number idx in the window
        deque<int> dq; // indicies of odd numbers in window

        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index

            if( dq.size() == k && nums[j] % 2 ) {
                // the number at the current index j is odd
                // and will push us beyond k
                // at the prior index of j we were in compliance

                // calculate how many windows we can build
                // left side length
                int ll = dq.front() - i + 1;
                // right side length
                int rl = (j-1) - dq.back() + 1;

                ans += ll * rl;

                // move the left index i forward till we are in compliance
                i = dq.front() + 1;
                dq.pop_front();

                // left most odd number idx is i (after we got into compliance)
                // right most odd number idx is j
            }

            if( nums[j] % 2 )
                dq.push_back(j);

        }
        // finish up
        if( dq.size() == k ) {
            int ll = dq.front() - i + 1;
            int rl = (n-1) - dq.back() + 1;
            ans += ll * rl;
        }

        return ans;
    }
};
