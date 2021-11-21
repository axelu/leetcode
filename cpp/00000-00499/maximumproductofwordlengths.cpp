
// 318. Maximum Product of Word Lengths
// https://leetcode.com/problems/maximum-product-of-word-lengths/
// day 27 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3757/




class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        vector<int> masks(n);
        int i,j,idx,mask=0;
        int ans = 0;

        // 1st word
        for(j = 0; j < words[0].size(); ++j) {
            idx = words[0][j]-'a';
            mask |= (1 << idx);
        }
        masks[0] = mask;

        for(i = 1; i < n; ++i) {
            mask = 0;
            for(j = 0; j < words[i].size(); ++j) {
                idx = words[i][j]-'a';
                mask |= (1 << idx);
            }
            masks[i] = mask;
            for(j = 0; j < i; ++j) {
                if( (masks[j] & masks[i]) == 0 ) {
                    ans = max(ans,(int)words[j].size()*(int)words[i].size());
                }
            }
        }

        return ans;
    }
};
