
// 132. Palindrome Partitioning II
// https://leetcode.com/problems/palindrome-partitioning-ii/



class Solution {
private:
    size_t N;
    int mem[2001][2001];

    bool isPalindrome(string& s, int b, int e) {
        // cout << "isPalindrome b=" << b << " e=" << e << endl;
        while(b < e) {
            if (s[b] != s[e]) return false;
            ++b;
            --e;
        }
        return true;
    }

    int rec(string& s, int b, int e) {
        // cout << "rec b=" << b << " e=" << e << endl;
        if( b == e ) return 0;
        if( mem[b][e] != -1 ) return mem[b][e];

        // greedy
        int cuts = e-b; // worst case
        int sub;
        for(int i = e; i >= b; --i) {
            if( isPalindrome(s,b,i) ) {
                if( i == e ) return 0;
                sub = rec(s,i+1,e);
                cuts = min(cuts,sub);
            }
        }

        return mem[b][e] = 1 + cuts;
    }



public:
    int minCut(string s) {
        N = s.size();
        if( N == 1 ) return 0;
        if( isPalindrome(s,0,N-1) ) return 0;


        for(int i = 0; i <=2000; ++i)
            for(int j = 0; j <= 2000; ++j)
                mem[i][j] = -1;

        // min answer: 0
        // max answer: N-1
        return rec(s,0,N-1);

    }
};
