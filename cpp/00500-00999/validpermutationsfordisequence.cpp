
// 903. Valid Permutations for DI Sequence
// https://leetcode.com/problems/valid-permutations-for-di-sequence/




class Solution {
private:
    int n;
    long MOD = 1000000007;
    int seen[201];
    int mem[201][201];

    long rec(string& s, int pos, int val) {


        if( pos == n )
            return 1;


        if( mem[val][pos] != -1 )
            return mem[val][pos];

        seen[val] = pos;

        long ret = 0;
        if( s[pos] == 'D' ) {
           // decreasing p[i] > p[i+1]
           for(int i = val-1; i >= 0; --i) {
                if( seen[i] == -1 ) {
                    ret = (ret + rec(s,pos+1,i)) % MOD;
                }
           }
        } else { // s[pos] == 'I'
           // increasing p[i] < p[i+1]
           for(int i = val+1; i <= n; ++i) {
                if( seen[i] == -1 ) {
                    ret = (ret + rec(s,pos+1,i)) % MOD;
                }
           }
        }

        // backtrack
        seen[val] = -1;

        return mem[val][pos] = ret;
    }
public:
    int numPermsDISequence(string& s) {
        n = s.size();

        for(int i = 0; i <= n; ++i) {
            seen[i] = -1;
            for(int j = 0; j <= n; ++j)
                mem[i][j] = -1;
        }


        int ans = 0;
        // top down dp
        for(int i = 0; i <= n; ++i) {
            ans = (ans + rec(s,0,i)) % MOD;
        }

        return ans;
    }
};
