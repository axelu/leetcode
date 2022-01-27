
// 639. Decode Ways II
// https://leetcode.com/problems/decode-ways-ii/
// day 10 July 2021 challenge
// https://leetcode.com/explore/featured/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3809/





class Solution {
private:
    long MOD = 1000000007;

    long rec(string& s, int i, long mem[]) {
        if( i < 0 )
            return 1;

        if( mem[i] != -1 )
            return mem[i];


        long ret = 0;

        if( s[i] == '*' ) {
            ret = 9 * rec(s,i-1,mem) % MOD;
            if( i > 0 ) {
                if( s[i-1] == '1' )
                    ret = (ret +  9 * rec(s,i-2,mem)) % MOD;
                else if( s[i-1] == '2' )
                    ret = (ret +  6 * rec(s,i-2,mem)) % MOD;
                else if( s[i-1] == '*' )
                    ret = (ret + 15 * rec(s,i-2,mem)) % MOD;
            }
        } else {
            if( s[i] != '0' )
                ret = rec(s,i-1,mem);
            if( i > 0 ) {
                if( s[i-1] == '1' )
                    ret = (ret + rec(s,i-2,mem)) % MOD;
                else if( s[i-1] == '2' && s[i] <= '6' )
                    ret = (ret + rec(s,i-2,mem)) % MOD;
                else if( s[i-1] == '*' )
                    if( s[i] <= '6' )
                        ret = (ret + 2 * rec(s,i-2,mem)) % MOD;
                    else
                        ret = (ret + rec(s,i-2,mem)) % MOD;
            }
        }

        return mem[i] = ret;
    }


public:
    int numDecodings(string& s) {
        int n = s.size(); // 1 <= s.length <= 1e5
        // leading zero's is invalid
        if( s[0] == '0' ) return 0;


        long mem[n];
        for(int i = 0; i < n; ++i)
            mem[i] = -1;

        return rec(s,n-1,mem);
    }
};
