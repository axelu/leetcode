
// 1177. Can Make Palindrome from Substring
// https://leetcode.com/problems/can-make-palindrome-from-substring/






class Solution {
private:
    int sum(int r, int chr, int bits[][26]) { // sum of range [0,r] inclusive
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bits[r][chr];
        return ret;
    }

    int sum(int l, int r, int chr, int bits[][26]) {
        return sum(r,chr,bits) - sum(l - 1,chr,bits);
    }


    void add(int idx, int delta, int n, int chr, int bits[][26]) {
        for(; idx < n; idx = idx | (idx + 1))
            bits[idx][chr] += delta;
    }


public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        // cout << "n " << n << endl;

        int bits[n][26];memset(bits,0,sizeof bits); // array of binary indexed trees (BITs), BIT is 0 indexed
        for(int i = 0; i < n; ++i) {
            int chr = s[i]-'a';
            add(i,1,n,chr,bits);
        }

        int q_sz = queries.size();
        // cout << "q_sz " << q_sz << endl;

        vector<bool> ans(q_sz,false);

        for(int i = 0; i < q_sz; ++i) {

            int odd_cnt = 0;
            for(int chr = 0; chr < 26; ++chr) {

                int cnt = sum(queries[i][0],queries[i][1],chr,bits);
                if( cnt % 2 )
                    ++odd_cnt;
            }

           if( (queries[i][1] - queries[i][0] + 1) % 2 ) { // odd substr length
                if( odd_cnt > 1 ) {
                    if( (odd_cnt-1)/2 <= queries[i][2] ) {
                        ans[i] = true;
                    }
                } else {
                    ans[i] = true;
                }

            } else { // even substr length
                if( odd_cnt/2 <= queries[i][2] ) {
                    ans[i] = true;
                }
            }
        }

        return ans;
    }
};
