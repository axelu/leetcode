
// 1830. Minimum Number of Operations to Make String Sorted
// https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/






class Solution {
private:
    long mod = 1000000007;
    int n;

    long bf(string& s, int i, int j) {
        cout << " bf " << s << " i " << i << " j " << j << endl;

        // swap chars at indicies i-1 and j
        swap(s,i,j);
        //if( i == n-1 && j == n-1 ) {
        //    return 1L;
        //}

        // reverse the suffix starting at i
        int l = i;
        int r = n-1;
        while( l < r ) {
            char t = s[r];
            s[r] = s[l];
            s[l] = t;
            ++l;
            --r;
        }

        return 1L;
    }

    long FACTORIAL[3001];

    long fact(long n) {
        long res = 1;
        for(long i = 2; i <= n; ++i) {
            res = (res * i) % mod;
            FACTORIAL[i] = res;
        }
        return res;
    }


    long long modPow(long long a, long long x) {
        // return a^x % mod
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a % mod
        return modPow(a,mod-2);
    }

    // modular division
    long modDivide(long a, long b) {
        // a = a % mod;
        long inv = modInverse(b);
        return (inv * a) % mod;
    }

    int findi(string& s, int i) {
        while( i >= 1 && s[i] >= s[i-1] )
            --i;
        return i;
    }

    int findj(string&s, int i) {
        int j = s.size()-1;
        while( j >= i && s[j] >= s[i-1] )
            --j;
        return j;
    }

    void swap(string&s, int i, int j) {
        // swap chars at indicies i-1 and j
        char t = s[j];
        s[j] = s[i-1];
        s[i-1] = t;
    }

    void swap(string&s, int i, int j, int cnt[]) {
        // swap chars at indicies i-1 and j
        char t = s[j];
        --cnt[t-'a'];
        s[j] = s[i-1];
        ++cnt[s[i-1]-'a'];
        s[i-1] = t;
    }

    long get_nbr_unique_permutations(string& s, int i, int cnt[]) {
        long f = 1L;
        for(int k = 0; k < 26; ++k) {
            // f = (f * fact(cnt[k])) % mod;
            f = (f * FACTORIAL[cnt[k]]) % mod;
        }

        return modDivide(FACTORIAL[n-i],f);
    }

public:
    int makeStringSorted(string s) {
        n = s.size();
        if( n == 1 )
            return 0;

        /*
        // brute force
        long ans = 0;
        int i = findi(s,n-1);
        while( i > 0 ) {
            int j = findj(s,i);
            long t = bf(s,i,j);
            ans = ans + t;
            i = findi(s,n-1);
        }
        cout << s << endl;
        return ans;
        */

        // precalculate factorials
        FACTORIAL[0] = 1;
        FACTORIAL[1] = 1;
        fact(3000);

        long ans = 0;
        int i = findi(s,n-1);
        // lets call s[i,n-1] our suffix
        // we need to keep track of the unique chars in our suffix
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(int k = i; k < n; ++k)
            ++cnt[s[k]-'a'];

        while( i > 0 ) {
            // there is some index j in our suffix with which we are swapping i-1
            // regardless of where j is, the suffix will remain sorted
            // after the swap, but then it gets reversed.
            // to get the suffix back sorted using the operation,
            // it will take number of operations equal to the number of unique permutations of suffix
            int j = findj(s,i);
            swap(s,i,j,cnt);
            long ops = get_nbr_unique_permutations(s,i,cnt);
            ans = (ans + ops) % mod;
            int i_new = findi(s,i);
            if( i_new != i ) {
                for(int k = i_new; k < i; ++k)
                    ++cnt[s[k]-'a'];
            }
            i = i_new;
        }

        return ans;
    }
};
