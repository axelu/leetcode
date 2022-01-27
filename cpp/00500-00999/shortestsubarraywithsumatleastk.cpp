
// 862. Shortest Subarray with Sum at Least K
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/





class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= nums.length <= 10^5, 10^5 <= nums[i] <= 10^5
        // worst case sum 10000000000 respectively -10000000000
        // INT_MAX         2147483647               -2147483648

        long prefixSum[n+1];
        prefixSum[0] = 0L;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + (long)nums[i];


        int ans = n+1;
        deque<int> dq; // stores indices with an increasing prefixSum
                       // indicies itself are strictly increasing from front to back
                       // so it is a strictly increasing monotonic double ended queue
        int l;
        for(int i = 0; i <= n; ++i) {

            while( !dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= (long)k ) {
                // we have found an ending i such that
                // subarraysum[dequeFrontIndex,i] >= k
                // remove front element of deque since there cannot be shorter subarray
                // because our deque has indices in increasing order from front to back
                l = i - dq.front();
                ans = min(ans,l);
                dq.pop_front();
            }

            while( !dq.empty() && prefixSum[i] <= prefixSum[dq.back()] ) {
                // we are only interested in indicies with an increasing prefixSum
                // because we will add our current index to the back of the queue,
                // we can eliminate all indicies from the back that have a
                // greater prefixSum than our current current prefixSum[i]
                dq.pop_back();
            }

            dq.push_back(i);

        }


        return ans == n+1 ? -1 : ans;
    }
};
