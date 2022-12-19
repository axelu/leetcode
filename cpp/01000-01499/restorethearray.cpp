
// 1416. Restore The Array
// https://leetcode.com/problems/restore-the-array/



class Solution {
private:
    long mod = 1000000007;
    int n;
    long K;
    char * _s;

    long mem[100000];

    long rec(int i) {
        if( i == n )
            return 1;

        if( _s[i] == '0' )
            return 0;

        if( mem[i] != -1 )
            return mem[i];

        long ret = 0;

        int a = 1;
        long t = _s[i] - '0';
        while( t <= K ) {
            ret = (ret + rec(i+a)) % mod;

            if( i + a == n )
                break;
            t  = t * 10 + ( _s[i+a] - '0' );
            ++a;
        }

        return mem[i] = ret;
    }

public:
    int numberOfArrays(string& s, int k) {
        n = s.size();
        K = k;
        _s = s.data();

        memset(mem,-1,sizeof mem);
        return rec(0);
    }
};
