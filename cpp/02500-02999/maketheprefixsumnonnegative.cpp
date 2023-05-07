
// 2599. Make the Prefix Sum Non-negative
// https://leetcode.com/problems/make-the-prefix-sum-non-negative/




class Solution {
public:
    int makePrefSumNonNegative(vector<int>& nums) {

        deque<int> dq;
        for(int x: nums)
            dq.push_back(x);

        int steps = 0;
        long long prefixSum = 0;

        priority_queue<int,vector<int>,greater<int>> pq;

        while( !dq.empty() ) {
            long long x = dq.front();
            dq.pop_front();

            pq.push(x);

            prefixSum = prefixSum + x;

            while( prefixSum < 0 ) {
                ++steps;
                prefixSum = prefixSum - pq.top();
                dq.push_back(pq.top());
                pq.pop();
            }
        }

        return steps;
    }
};
