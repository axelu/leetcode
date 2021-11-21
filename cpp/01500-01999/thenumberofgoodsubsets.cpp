
// 1994. The Number of Good Subsets
// https://leetcode.com/problems/the-number-of-good-subsets/




// Prime Factorization 2 - 30 inclusive
// 2: 2
// 3: 3
// 4: 2 2
// 5: 5
// 6: 2 3
// 7: 7
// 8: 2 2 2
// 9: 3 3
// 10: 2 5
// 11: 11
// 12: 2 2 3
// 13: 13
// 14: 2 7
// 15: 3 5
// 16: 2 2 2 2
// 17: 17
// 18: 2 3 3
// 19: 19
// 20: 2 2 5
// 21: 3 7
// 22: 2 11
// 23: 23
// 24: 2 2 2 3
// 25: 5 5
// 26: 2 13
// 27: 3 3 3
// 28: 2 2 7
// 29: 29
// 30: 2 3 5

class Solution {
private:
    // prime factorization
    void primeFactors(int n) {
        // the number of 2s that divide n
        while(n % 2 == 0) {
            cout << 2 << " ";
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                cout << i << " ";
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 )
            cout << n << " ";
    }

    bool primeFactors2(int n, int& mask) {
        // the number of 2s that divide n
        while(n % 2 == 0) {
            if( (mask >> 2) & 1 )
                return false;
            mask |= 1 << 2;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                if( (mask >> i) & 1 )
                    return false;
                mask |= 1 << i;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            if( (mask >> n) & 1 )
                return false;
            mask |= 1 << n;
        }

        return true;
    }

    long cnt[31];
    long MOD = 1000000007;
    long onefactor;

    // https://en.wikipedia.org/wiki/Modular_exponentiation
    long modular_pow(unsigned long long base, int exponent) {
        unsigned long long c = 1;
        for(int i = 0; i < exponent; ++i)
            c = (c * base) % MOD;
        return c;
    }

    long genSubsequences(vector<array<int,2>>& arr, int i, vector<array<int,2>>& subsequence, int mask) {
        if( i == arr.size() ) {
            int l = subsequence.size();
            if( l != 0 ) {
                // we have arrived at a good non-empty subseqence
                // calculate our subsequences frequency in nums
                // this is w/o the number 1
                long ret = 1L;
                for(int k = 0; k < l; ++k)
                    ret = (ret * cnt[subsequence[k][0]]) % MOD;

                // accounting for the number 1
                ret = (ret + ((onefactor * ret) % MOD)) % MOD;

                return ret;
            } else {
                return 0L;
            }
        }

        // we have a choice
        // don't include element at current index
        long ret = genSubsequences(arr,i+1,subsequence,mask) % MOD;

        // include element at current index
        // we can only include the current element
        // if the prime factors remain unique
        bool f = true;
        for(int k = 2; k <= 30; ++k) {
            if( !((arr[i][1]>>k) & 1) )
                continue;

            if( (mask >> k ) & 1 ) {
                f = false;
                break;
            }

            mask |= 1 << k;
        }
        if( f ) {
            subsequence.push_back(arr[i]);
            ret = (ret + genSubsequences(arr,i+1,subsequence,mask)) % MOD;
            subsequence.pop_back();
        }

        return ret;
    }

public:
    int numberOfGoodSubsets(vector<int>& nums) {
        // 1 <= nums[i] <= 30

        // consider only the numbers which have a good prime factorization,
        // meaning composite numbers that are the product of distinct primes.
        // primes between 1 and 30 inclusive have a 'good' prime factorization
        // primes between 1 and 30 inclusive (there are 10):
        // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
        // which of the remaining numbers have a 'good prime factorization'?
        // remaining numbers: 4,6,8,9,10,12,14,15,16,18,20,21,22,24,25,26,27,28,30
        /*
        for(int i = 2; i < 31; ++i) {
            cout << i << ": ";
            primeFactors(i);
            int mask = 0;
            bool f = primeFactors2(i,mask);
            if( f ) cout << "good";
            else cout << "bad";
            cout << endl;
        }
        */


        memset(cnt,0,sizeof cnt);
        for(int i = 0; i < nums.size(); ++i)
            ++cnt[nums[i]];

        vector<array<int,2>> arr; // value,mask
        int mask;
        for(int i = 2; i <= 30; ++i)
            if( cnt[i] > 0 ) {
                mask = 0;
                if( primeFactors2(i,mask) )
                    arr.push_back({i,mask});
            }

        if( arr.size() == 0 ) // no numbers with good primefactorization in nums
            return 0;

        // we will generate all possible 'good' subsets
        // primes are greater than 1
        // hence we will need to account for the number of ones we have
        // by multiplying the number of good subsequences times the number
        // of possible permutations we can get from the number of ones we have
        // 2^n - 1 with n being the number of ones
        // n can be large, worst case 99999
        onefactor = modular_pow(2,cnt[1]) - 1;

        mask = 0;
        vector<array<int,2>> subsequence;
        return genSubsequences(arr,0,subsequence,mask);
    }
};
