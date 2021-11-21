
// 1940. Longest Common Subsequence Between Sorted Arrays
// https://leetcode.com/problems/longest-common-subsequence-between-sorted-arrays/




class Solution {
public:
    vector<int> longestCommomSubsequence(vector<vector<int>>& arrays) {
        int n = arrays.size();

        int cnt[101];memset(cnt,0,sizeof cnt);
        vector<int> ans;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < arrays[i].size(); ++j) {
                ++cnt[arrays[i][j]];
                if( i == n-1 && cnt[arrays[i][j]] == n )
                    ans.push_back(arrays[i][j]);
            }

       return ans;
    }
};
