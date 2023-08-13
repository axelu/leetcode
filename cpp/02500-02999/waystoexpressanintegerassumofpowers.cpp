
// 2787. Ways to Express an Integer as Sum of Powers
// https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/




class Solution {
private:
    long mod = 1000000007;
    long mem[301][301];

    long rec(long i, long x, long k) {
        long a = pow(i,x);
        if( a > k )
            return 0LL;
        if( a == k )
            return 1LL;

        if( mem[i][k] != -1 )
            return mem[i][k];

        // we have a choice
        //    use i OR
        //    skip i

        long ret = rec(i+1,x,k-a);
        ret = (ret + rec(i+1,x,k)) % mod;

        return mem[i][k] = ret;
    }

public:
    int numberOfWays(int n, int x) {
        memset(mem,-1,sizeof mem);
        return rec(1,x,n);
    }
};
