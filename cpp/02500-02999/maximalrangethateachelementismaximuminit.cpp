
// 2832. Maximal Range That Each Element Is Maximum in It
// https://leetcode.com/problems/maximal-range-that-each-element-is-maximum-in-it/





class Solution {
public:
    vector<int> maximumLengthOfRanges(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        // monotonic decreasing stack
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        // left to right
        int l2r[n];
        for(int i = 0; i < n; ++i) {
            while( !pq.empty() && pq.top()[0] < nums[i] )
                pq.pop();

            l2r[i] = !pq.empty() ? pq.top()[1] + 1 : 0;
            pq.push({nums[i],i});
        }

        // clear queue for reuse
        while( !pq.empty() )
            pq.pop();

        // right to left
        for(int i = n-1; i >= 0; --i) {
            while( !pq.empty() && pq.top()[0] < nums[i] )
                pq.pop();

            int r2l = !pq.empty() ? pq.top()[1] - 1 : n-1;
            ans[i] = r2l - l2r[i] + 1;
            pq.push({nums[i],i});
        }

        return ans;
    }
};
