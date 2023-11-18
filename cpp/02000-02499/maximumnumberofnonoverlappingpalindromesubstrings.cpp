
// 2472. Maximum Number of Non-overlapping Palindrome Substrings
// https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/






class Solution {
private:
    int seen[2000];

    int solve(string& s, int n, int b, int e, int k) {
        if( b < 0 || e > n-1 )
            return 0;

        if( s[b] != s[e] || seen[b] )
            return 0;

        if( e - b + 1 >= k ) {
            // mark seen[b,e] inclusive as part of a palindrome
            for(int i = b; i <= e; ++i)
                seen[i] = 1;
            return 1;
        }

        // expand our palindrome
        return solve(s,n,b-1,e+1,k);
    }

public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        int ans = 0;

        // seen[i] set to 1 if idx i is a member of a palindrome
        memset(seen,0,sizeof seen);

        for(int i = 0; i < n; ++i) {
            // we will attempt to build a palindrome around i (odd length palindrome) or
            // around i and i+1 (even length palindrome)
            // we only need to check up to length of k respectively k + 1

            if( !seen[i] )
                ans += solve(s,n,i,i,k);

            if( i+1 < n && s[i] == s[i+1] && !seen[i] )
                ans += solve(s,n,i,i+1,k);
        }

        return ans;
    }
};
