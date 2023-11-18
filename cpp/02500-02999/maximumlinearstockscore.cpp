
// 2898. Maximum Linear Stock Score
// https://leetcode.com/problems/maximum-linear-stock-score/






class Solution {
public:
    long long maxScore(vector<int>& prices) {
        int n = prices.size(); // 1-indexed !!!

        // prices[i] is the price of a particular stock on the ith day
        // select some of the elements of prices such that the selection is linear
        // let indexes be a 1-indexed integer array of length k which is a subsequence of the array [1, 2, ..., n]
        // indexes is linear if:
        // For every 1 < j <= k, prices[indexes[j]] - prices[indexes[j - 1]] == indexes[j] - indexes[j - 1]
        // resolve to:           prices[indexes[j]] - indexes[j]             == prices[indexes[j - 1]] - indexes[j - 1]

        // for each index i lets calculate prices[i] - i
        // we then can group indexes that have the same result

        unordered_map<int,long long> um;
        for(int i = 1; i <= n; ++i) {
            int key = prices[i-1] - i;
            um[key] += prices[i-1];
        }

        long long ans = 0;
        for(auto& p: um)
            ans = max(ans, p.second);

        return ans;
    }
};
