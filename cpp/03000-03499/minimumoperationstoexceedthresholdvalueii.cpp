
// 3066. Minimum Operations to Exceed Threshold Value II
// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/




class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        // it is guaranteed that an answer always exists
        int n = nums.size();

        sort(nums.begin(),nums.end());
        if( nums[0] >= k )
            return 0;

        priority_queue<long,vector<long>,greater<long>> pq;
        for(int i = 0; i < n; ++i)
            pq.push(nums[i]);

        int ans = 0;
        while( !pq.empty() && pq.top() < k ) {
            ++ans;

            long x = pq.top(); pq.pop();
            long y = pq.top(); pq.pop();

            pq.push(min(x,y) * 2L + max(x,y));
        }

        return ans;
    }
};
