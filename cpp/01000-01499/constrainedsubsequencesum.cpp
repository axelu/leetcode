
// 1425. Constrained Subsequence Sum
// https://leetcode.com/problems/constrained-subsequence-sum/




class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        // from the hint:
        //     let dp[i] be the solution for the prefix of the array that ends at i,
        //     if the element at i is in the subsequence.
        //     dp[i] = nums[i] + max(0, dp[i-k], dp[i-k+1], ..., dp[i-1])

        int n = nums.size();

        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) // keep the closer one
                    return true;
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        int dp[n];
        dp[0] = nums[0];
        pq.push({dp[0],0});

        int ans = dp[0];

        int i = 0; // left index
        for(int j = 1; j < n; ++j) {

            while( pq.top()[1] < j-k )
                pq.pop();

            dp[j] = nums[j] + max(0,pq.top()[0]);
            pq.push({dp[j],j});

            ans = max(ans,dp[j]);
        }

        return ans;
    }
};
