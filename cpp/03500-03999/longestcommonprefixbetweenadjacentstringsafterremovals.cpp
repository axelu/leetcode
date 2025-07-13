
// 3598. Longest Common Prefix Between Adjacent Strings After Removals
// https://leetcode.com/problems/longest-common-prefix-between-adjacent-strings-after-removals/



class Solution {
private:
    int common_prefix_length(vector<string>& words, int i, int j) {
        int i_sz = words[i].size();
        int j_sz = words[j].size();
        int k = 0;
        int k_max = min(i_sz, j_sz);
        for(; k < k_max; ++k)
            if( words[i][k] != words[j][k] )
                break;
        return k;
    }
public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();

        vector<int> ans(n, 0);

        if( n < 3 )
            return ans;

        // 0  1  2  3  4  5  6  7  8  9
        // 01 12 23 34 45 56 67 78 89 -

        // pass 1 left to right
        vector<int> cpl(n);
        vector<int> l2r(n);
        for(int i = 0; i < n-1; ++i) {
            cpl[i] = common_prefix_length(words, i, i+1);
            if( i == 0 )
                l2r[0] = cpl[0];
            else
                l2r[i] = max(cpl[i], l2r[i-1]);
        }
        // pass 2 right to left
        vector<int> r2l(n);
        for(int i = n-2; i >= 0; --i) {
            if( i == n-2 )
                r2l[n-2] = cpl[n-2];
            else
                r2l[i] = max(cpl[i], r2l[i+1]);
        }

        for(int i = 0; i < n; ++i) {
            if( i == 0 ) {
                ans[i] = r2l[1];
            } else if( i == n-1 ) {
                ans[i] = l2r[n-3];
            } else {
                // calculate common prefix length between
                // word i-1 and word i+1
                int _cpl = common_prefix_length(words, i-1, i+1);
                // left
                int lft = i-2 >= 0 ? l2r[i-2] : 0;
                // right
                int rgt = r2l[i+1];

                ans[i] = max({_cpl, lft, rgt});
            }
        }

        return ans;
    }
};
