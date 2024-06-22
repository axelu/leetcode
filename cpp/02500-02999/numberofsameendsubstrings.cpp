
// 2955. Number of Same-End Substrings
// https://leetcode.com/problems/number-of-same-end-substrings/






class Solution {
public:
    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        int n = s.size();

        // to lookup the count of a given char in range[l,r]
        // we will make a prefixSum for each char
        int prefixSum[n+1][26];
        for(int c = 0; c < 26; ++c)
            prefixSum[0][c] = 0;

        for(int i = 1; i <= n; ++i) {
            for(int c = 0; c < 26; ++c)
                prefixSum[i][c] = prefixSum[i-1][c];
            ++prefixSum[i][s[i-1] - 'a'];
        }

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int q = 0; q < q_sz; ++q) {
            int l = queries[q][0];
            int r = queries[q][1];
            int t = 0;
            for(int c = 0; c < 26; ++c) {
                int c_cnt = prefixSum[r+1][c] - prefixSum[l][c];
                t += c_cnt * (c_cnt + 1)/2;
            }

            ans[q] = t;
        }


        return ans;
    }
};
