
// 1456. Maximum Number of Vowels in a Substring of Given Length
// https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/


class Solution {
public:
    int maxVowels(string s, int k) {
        int n = s.size();

        int ans = 0;

        char c;
        int cnt = 0;
        int i = 0;
        for(int j = 0; j < n; ++j) {
            c = s[j];
            if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' )
                ++cnt;

            if( j+1 < k )
                continue;

            ans = max(ans,cnt);
            c = s[i];
            if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' )
                --cnt;
            ++i;
        }

        return ans;
    }
};
