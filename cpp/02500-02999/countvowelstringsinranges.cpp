
// 2559. Count Vowel Strings in Ranges
// https://leetcode.com/problems/count-vowel-strings-in-ranges/


class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int n = words.size();
        int t[n];memset(t,0,sizeof t);
        for(int i = 0; i < n; ++i) {
            char cf = words[i].front();
            char cb = words[i].back();
            if( (cf == 'a' || cf == 'e' || cf == 'i' || cf == 'o' || cf == 'u') &&
                (cb == 'a' || cb == 'e' || cb == 'i' || cb == 'o' || cb == 'u') )
                t[i] = 1;
        }

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + t[i-1];

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i)
            ans[i] = prefixSum[queries[i][1]+1] - prefixSum[queries[i][0]];

        return ans;
    }
};
