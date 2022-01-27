
// 2099. Find Subsequence of Length K With the Largest Sum
// https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/




class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        auto cmp1 = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] < b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp1)> pq1(cmp1);
        for(int i = 0; i < nums.size(); ++i)
            pq1.push({nums[i],i});

        auto cmp2 = [](const array<int,2>& a, const array<int,2>& b){
            return a[1] > b[1];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp2)> pq2(cmp2);
        int c = 0;
        while( c < k ) {
            pq2.push({pq1.top()[0],pq1.top()[1]});
            pq1.pop();
            ++c;
        }

        c = 0;
        vector<int> ans(k);
        while( c < k ) {
            ans[c] = pq2.top()[0];
            pq2.pop();
            ++c;
        }

        return ans;
    }
};
