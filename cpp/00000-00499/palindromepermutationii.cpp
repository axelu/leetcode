
// 267. Palindrome Permutation II
// https://leetcode.com/problems/palindrome-permutation-ii/


class Solution {
private:
    vector<string> ans;

    void rec(int cnt[], int n, int l, int r, string& t) {
        // cout << "rec l " << l << " r " << r << endl;
        if( l == r ) {
            for(int i = 0; i < 26; ++i) {
                if( cnt[i] ) {
                    t[l] = i+'a';
                    ans.push_back(t);
                    return;
                }
            }
        } else if( l+1 == r ) {
            for(int i = 0; i < 26; ++i) {
                if( cnt[i] == 2 ) {
                    t[l] = i+'a';
                    t[r] = i+'a';
                    ans.push_back(t);
                    return;
                }
            }
        } else {
            for(int i = 0; i < 26; ++i) {
                if( cnt[i] != 0 && cnt[i] >= 2 ) {
                    t[l] = i+'a';
                    t[r] = i+'a';
                    cnt[i] -= 2;
                    rec(cnt,n,l+1,r-1,t);
                    // backtrack
                    cnt[i] += 2;
                }
            }
        }
    }

public:
    vector<string> generatePalindromes(string s) {
        int n = s.size();

        // if n is even, all char counts must be even
        // if n is odd, one char count must be odd
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c : s)
            ++cnt[c-'a'];

        if( n % 2 == 0 ) {
            for(int i = 0; i < 26; ++i)
                if( cnt[i] % 2 == 1 )
                    return {};
        } else {
            int o = 0;
            for(int i = 0; i < 26; ++i)
                if( cnt[i] % 2 == 1 )
                    ++o;
            if( o > 1 )
                return {};
        }

        string t(n,'#');
        rec(cnt,n,0,n-1,t);
        return ans;
    }
};
