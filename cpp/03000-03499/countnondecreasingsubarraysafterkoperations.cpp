
// 3420. Count Non-Decreasing Subarrays After K Operations
// https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/





class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        long long ans = 0LL;

        // we can only increase elements in nums
        // sliding window
        // we will go from right to left however
        // we will use a deque
        // the front of the deque holds smaller left side aka front of window
        //     this is where we add when we expand the window
        // the back of the deque with that has larger right side aka back of
        // the sliding window
        //     this is where we take away when we shrink the window
        deque<pair<int,int>> dq; // val, count
        long long ops = 0;
        int j = n-1;                    // right index
        for(int i = n-1; i >= 0; --i) { // left index
            int x = nums[i];
            int cnt = 1;
            // if we have values smaller than us to our right,
            // then we need to elevate those
            while( !dq.empty() && dq.front().first <= x ) {
                ops += (long long)(x - dq.front().first) * (long long)dq.front().second;
                cnt += dq.front().second;
                dq.pop_front();
            }
            dq.push_front({x,cnt});

            // shrink the window
            while( ops > k && !dq.empty() ) {
                int val = dq.back().first;
                int occ = dq.back().second;
                dq.pop_back();
                ops -= (long long)(val - nums[j]);
                --occ;
                if( occ > 0 )
                    dq.push_back({val,occ});
                --j;
            }
            // all subarrays ending at j
            ans += (long long)(j-i+1);
        }

        return ans;
    }
};
