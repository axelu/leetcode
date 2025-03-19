
// 3472. Longest Palindromic Subsequence After at Most K Operations
// https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/





class Solution {
private:
    // TODO we could pre-calc every possible combination
    int get_cost(char a, char b) {
        if( a == b )
            return 0;

        if( b < a )
            swap(a,b);

        int cost1 = b - a;
        int cost2 = (a + 26) - b;

        return min(cost1, cost2);
    }

    int mem[200][200][201];

    int rec(string& s, int i, int j, int k) {
        if( i == j )
            return 1;
        if( i > j )
            return 0;

        if( mem[i][j][k] != -1 )
            return mem[i][j][k];


        // we have a choice
        //     if s[i] == s[j] we advance both i and j
        //     we make s[i] == s[j] if we have enough k
        //         then we advance both
        //     we advance i
        //     we advance j

        int a = 0;
        if( s[i] == s[j] ) {
            a = 2 + rec(s, i+1, j-1, k);
            return mem[i][j][k] = a;
        }

        int cost = get_cost(s[i], s[j]);
        int b = 0;
        if( cost <= k )
            b = 2 + rec(s, i+1, j-1, k-cost);

        int c = rec(s, i+1, j, k);
        int d = rec(s, i, j-1, k);

        return mem[i][j][k] = max({b, c, d});
    }

public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        memset(mem,-1,sizeof mem);
        return rec(s, 0, n-1, k);
    }
};
