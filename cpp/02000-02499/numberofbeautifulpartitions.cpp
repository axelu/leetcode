
// 2478. Number of Beautiful Partitions
// https://leetcode.com/problems/number-of-beautiful-partitions/




class Solution {
private:
    long mod = 1000000007;
    long mem[1000][1001];

    bool isPrime(char c) {
        return c == '2' || c == '3' || c == '5' || c == '7';
    }

    long rec(const string& s, const int n, const int pos, const int k, const int minLength) {
        // it is guaranteed that we have minLength chars left
        if( !isPrime(s[pos]) )
            return 0L;

        if( k == 1 )
            return !isPrime(s[n-1]) ? 1L : 0L;

        if( mem[pos][k] != -1 )
            return mem[pos][k];

        long ret = 0L;

        int i_min = pos + minLength - 1;
        // we will need to leave a minimum of (k-1) * minLength characters after us
        int i_max = n - ((k-1) * minLength) - 1;
        for(int i = i_min; i <= i_max; ++i) {
            if( isPrime(s[i]) )
                continue;

            ret = (ret + rec(s,n,i+1,k-1,minLength)) % mod;
        }

        return mem[pos][k] = ret;
    }

public:
    int beautifulPartitions(string s, int k, int minLength) {
        int n = s.size();

        // there is no way for a substring of length 1,
        // because it has to start with a prime and end with a non-prime,
        // hence minLength has to be at least 2
        minLength = max(2,minLength);

        if( k * minLength > n )
            return 0;

        if( k == 1 ) {
            // s has to start with a prime and end with a non-prime
            if( isPrime(s[0]) && !isPrime(s[n-1]) )
                return 1;
            else
                return 0;
        }

        memset(mem,-1,sizeof mem);
        return rec(s,n,0,k,minLength);
    }
};
