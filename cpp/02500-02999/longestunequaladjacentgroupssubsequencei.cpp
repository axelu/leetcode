
// 2900. Longest Unequal Adjacent Groups Subsequence I
// https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/






class Solution {
public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        int lst0[n];
        lst0[n-1] = -1;
        int lst1[n];
        lst1[n-1] = -1;

        for(int i = n-2; i >= 0; --i) {
            lst0[i] = groups[i+1] == 0 ? i+1 : lst0[i+1];
            lst1[i] = groups[i+1] == 1 ? i+1 : lst1[i+1];
        }

        vector<string> ans;
        for(int i = 0; i != -1; ) {
            ans.push_back(words[i]);
            i =  groups[i] == 0 ? lst1[i] : lst0[i];
        }

        return ans;
    }
};
