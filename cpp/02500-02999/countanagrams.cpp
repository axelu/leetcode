
// 2514. Count Anagrams
// https://leetcode.com/problems/count-anagrams/




/* for each word in s we need to find the number of distinct permutations we can make
 * https://stats.libretexts.org/Courses/Las_Positas_College/Math_40%3A_Statistics_and_Probability/04%3A_Probability_and_Counting/4.04%3A_Counting_Rules/4.4.02%3A_Permutations_with_Similar_Elements
 * Definition: Permutations with Similar Elements
 * The number of permutations of n elements taken 𝑛 at a time, with 𝑟1 elements of one kind, 𝑟2  elements of another kind, and so on, is
 * ( n! ) / ( 𝑟1!𝑟2!…𝑟𝑘! )
 *
 */


// initialize once
long  factorial[100001];
bool init = false;

class Solution {
private:
    long mod = 1000000007;

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


public:
    int countAnagrams(string s) {

        if( !init ) {
            init = true;

            // pre-calculate modular factorial
            factorial[0] = 1L;
            factorial[1] = 1L;
            for(long i = 2; i <= 100000; ++i)
                factorial[i] = (factorial[i-1] * i) % mod;

            // TODO precompute the inverse of the factorials

        }

        long ans = 1L;

        vector<string> v;
        stringstream ss(s);
        string word;
        while( getline(ss,word,' ') ) {
            int n = word.size();
            long cnt[26];memset(cnt,0,sizeof cnt);
            for(char c: word)
                ++cnt[c-'a'];

            long divisor = 1L;
            for(int i = 0; i < 26; ++i)
                divisor = (divisor * factorial[cnt[i]]) % mod; // modular multiplication

            // modular division
            long f = modDivide(factorial[n], divisor);

            ans = (ans * f) % mod; // modular multiplication
        }

        return ans;
    }
};
