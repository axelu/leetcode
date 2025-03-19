
// 3343. Count Number of Balanced Permutations
// https://leetcode.com/problems/count-number-of-balanced-permutations/





// initialize once, precompute factorial and modinverse
long long factorial[41];
long long inverse[41];
bool init = false;

class Solution {
private:
    int cnt[10];
    int n;
    int sum2;

    const long mod = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

    // worst case:
    // we have 10 digits to distribute
    // we could have up to 40 even positions
    // sum could be 40 * 9 = 360
    //     (40 even positions because max n = 80, 9 is the largest digit)
    long mem[10][41][361];

    long rec(int i, int even, int even_sum) {
        // cout << "rec i " << i << " even " << even << " even_sum " << even_sum << endl;
        // i digit that we are distributing
        // even number of even positions remaining
        // even_sum

        if( even_sum > sum2 )
            return 0L;

        if( i == 10 )
            return even_sum == sum2 ? 1L : 0L;

        if( mem[i][even][even_sum] != -1 )
            return mem[i][even][even_sum];

        long ret = 0L;

        // number odd positions remaining
        // we distributed all digits before us
        int distributed = 0;
        for(int k = 0; k < i; ++k)
            distributed += cnt[k];
        int odd = n - distributed - even;

        // let mx be the count of the current digit
        // we distribute the current digit as follows
        // even positions | odd positions
        // mx               0
        // mx-1             1
        // ..               ..
        // 0                mx
        int mx = cnt[i];
        for(int keven = min(mx, even); keven >= 0; --keven) {
            int kodd = mx - keven;
            if( kodd > odd )
                break;

            // ways to distribute keven over even remaining positions
            long a = modCombinations(even, keven);

            // ways to distribute kodd over odd remaining positions
            long b = modCombinations(odd, kodd);

            // ret = ret + (a * b * rec(i+1, even - keven, even_sum + (keven * i)));
            ret = (ret + (((a * b) % mod) * rec(i+1, even - keven, even_sum + (keven * i))) % mod) % mod;
        }

        return mem[i][even][even_sum] = ret;
    }


public:
    int countBalancedPermutations(string num) {
        if( !init ) {
            init = true;

            factorial[0] = 1LL;
            inverse[0] = 1LL;
            for(int i = 1; i <= 40; ++i) {
                factorial[i] = (factorial[i-1] * i) % mod;
                inverse[i]   = modInverse(factorial[i]);
            }
        }

        n = num.size(); // 2 <= num.length <= 80

        // we have digits 0..9
        // we need to distribute them to the even and odd positions
        // the sum of the even and odd positions has to be equal in the end

        memset(cnt,0,sizeof cnt);
        int sum = 0;
        for(char c: num) {
            ++cnt[c-'0'];
            sum += c-'0';
        }
        // we have no solution if sum cannot be divided by 2
        if( sum % 2 )
            return 0;
        sum2 = sum / 2;

        // number of even positions
        int even = n / 2;
        if( n % 2 )
            ++even;

        memset(mem,-1,sizeof mem);
        return rec(0, even, 0);
    }
};
