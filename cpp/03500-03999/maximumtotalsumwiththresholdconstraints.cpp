
// 3763. Maximum Total Sum with Threshold Constraint
// https://leetcode.com/problems/maximum-total-sum-with-threshold-constraints/



class Solution {
public:
    long long maxSum(vector<int>& nums, vector<int>& threshold) {
        int n = nums.size(); // nums.size() == threshold.size()
        long long ans = 0LL;

        // at every step i with 1 <= i <= n, look at all threshold j
        // where threshold[j] <= step and use the largest one (greedy)

        vector<pair<int,int>> arr(n);
        for(int i = 0; i < n; ++i)
            arr[i] = {threshold[i], nums[i]};
        sort(begin(arr),end(arr),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        priority_queue<int> pq;
        int i = 0; // index in arr
        for(int step = 1; step <= n; ++step) {
            while( i < n && arr[i].first <= step ) {
                pq.push(arr[i].second);
                ++i;
            }

            if( pq.empty() )
                break;

            ans += (long long)pq.top();
            pq.pop();
        }

        return ans;
    }
};
