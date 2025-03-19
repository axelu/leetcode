
// 3456. Find Special Substring of Length K
// https://leetcode.com/problems/find-special-substring-of-length-k/





class Solution {
public:
    bool hasSpecialSubstring(string s, int k) {
        int n = s.size();

        int cnt[26];memset(cnt,0,sizeof cnt);

        // sliding window
        int unique = 0;
        int i = 0;                  // left index
        for(int j = 0; j < n; ++j) {// right index
            int cj = s[j] - 'a';
            ++cnt[cj];
            if( cnt[cj] == 1 )
                ++unique;

            if( j-i+1 == k ) {
                if( unique == 1 ) {
                    bool left_different = true;
                    if( i > 0 && s[i-1] == s[j] )
                        left_different = false;
                    bool right_different = true;
                    if( j < n-1 && s[j] == s[j+1] )
                        right_different = false;

                    if( left_different && right_different )
                        return true;
                }

                int ci = s[i] - 'a';
                --cnt[ci];
                if( cnt[ci] == 0 )
                    --unique;
                ++i;
            }
        }

        return false;
    }
};
