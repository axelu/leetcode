
// 1220. Count Vowels Permutation
// https://leetcode.com/problems/count-vowels-permutation/
// day 4 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3802/




class Solution {
private:
    long MOD = 1000000007;
    int N;
    long mem[20000][5];

    long rec(int pos, int vowel) {

        if( pos == N-1 )
            return 1;

        if( mem[pos][vowel] != -1 )
            return mem[pos][vowel];

        long ret = 0;

        if( vowel == 0 ) {                      // a
            ret = (ret + rec(pos+1,1)) % MOD;   // e
        } else if( vowel == 1 ) {               // e
            ret = (ret + rec(pos+1,0)) % MOD;   // a
            ret = (ret + rec(pos+1,2)) % MOD;   // i
        } else if( vowel == 2 ) {               // i
            ret = (ret + rec(pos+1,0)) % MOD;   // a
            ret = (ret + rec(pos+1,1)) % MOD;   // e
            ret = (ret + rec(pos+1,3)) % MOD;   // o
            ret = (ret + rec(pos+1,4)) % MOD;   // u
        } else if( vowel == 3 ) {               // o
            ret = (ret + rec(pos+1,2)) % MOD;   // i
            ret = (ret + rec(pos+1,4)) % MOD;   // u
        } else if( vowel == 4 ) {               // u
            ret = (ret + rec(pos+1,0)) % MOD;   // a
        }

        return mem[pos][vowel] = ret;
    }


public:
    int countVowelPermutation(int n) {
        // vowels  0 1 2 3 4
        //         a,e,i,o,u

        N = n;

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < 5; ++j)
                mem[i][j] = -1;

        long ans = 0;
        for(int i = 0; i < 5; ++i) {
            ans = (ans + rec(0,i)) % MOD;
        }

        return (int)ans;
    }
};
