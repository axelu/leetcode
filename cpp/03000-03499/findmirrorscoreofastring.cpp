
// 3412. Find Mirror Score of a String
// https://leetcode.com/problems/find-mirror-score-of-a-string/






class Solution {
private:
    //                          abcdefghijklmnopqrstuvwxyz
    //                          01234567890123456789012345
    // const string alpha_rev = "zyxwvutsrqponmlkjihgfedcba";

public:
    long long calculateScore(string s) {
        int n = s.size();

        vector<int> pos[26];

        long long ans = 0LL;

        for(int i = 0; i < n; ++i) {
            int c_idx  = s[i] - 'a';
            int c_ridx = 25 - c_idx;

            if( pos[c_ridx].empty() ) {
                pos[c_idx].push_back(i);

            } else {
                int j = pos[c_ridx].back();
                ans += (long long)(i-j);
                pos[c_ridx].pop_back();
            }
        }

        return ans;
    }
};
