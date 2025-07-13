
// 3518. Smallest Palindromic Rearrangement II
// https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/






/* resources
     https://brilliant.org/wiki/permutations-with-repetition/
     https://swiyu.wordpress.com/2012/10/11/find-all-permutation-find-kth-permutation/
     formula permutations with repetition n!/(n1!n2!...nk!)
     https://www.geeksforgeeks.org/find-n-th-lexicographically-permutation-string-set-2/

     if we have an odd length, the odd cnt char will need to go in the middle
     so we don't need to worry about it
     after that, lets just focus on the half length string and rephrase the problem:
     return the k-th lexicographically smallest permutation of string s

     example s = "bbcccaaaaaacccbb", k = 10
     the half string lexicographically smallest is: aaabbccc
     if we go from right to left and calculate the permutations with repetition
     we can achieve then we can determine where to start to permute
     aaabbccc
        -----
    5!(2!3!) = 10, so we know we can get 10 permutations just looking bbccc, so aaa is fixed
    ans hence aaacccbb -> full answer aaacccbbbbcccaaa

    example s = "bbcccaaaaaacccbb", k = 3
    aaabbccc
        ----
    4!(1!3!) = 4, we know we can get 4 permutations by permutating the last 4 chars bccc
    bccc 1
    cbcc 2
    ccbc 3 <- this is our answer, hence half answer aaabccbc -> full answer aaabccbccbccbaaa
    cccb 4


 */

// initialize once
unordered_map<int,int> pfs[5001];
bool init = false;

class Solution {
private:
    // prime factorization fills map with count of prime factors
    unordered_map<int,int> primeFactors(int n) {
        // um -> key: prime factor, value: count
        unordered_map<int,int> um;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++um[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                ++um[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            ++um[n];
        }

        return um;
    }

    unsigned long long solve(int len, int freq[]) {
        // dividend
        if( len == 1 )
            return 1;
        unordered_map<int,int> dividend;
        for(int j = 2; j <= len; ++j) {
            for(auto pf: pfs[j])
                dividend[pf.first] += pf.second;
        }

        // divisor
        unordered_map<int,int> divisor;
        for(int i = 0; i < 26; ++i) {
            if( freq[i] < 2 )
                continue;
            for(int j = 2; j <= freq[i]; ++j)
                for(auto pf: pfs[j])
                    divisor[pf.first] += pf.second;
        }

        // solve
        for(int j = 2; j < 5000; ++j) { // largest prime factor 4999
            if( dividend.find(j) == dividend.end() || divisor.find(j) == divisor.end() )
                continue;

            if( dividend[j] == divisor[j] ) {
                dividend.erase(j);
                divisor.erase(j);
            } else if( dividend[j] > divisor[j] ) {
                dividend[j] = dividend[j] - divisor[j];
                divisor.erase(j);
            } else { // dividend[j] < divisor[j]
                divisor[j] = divisor[j] - dividend[j];
                dividend.erase(j);
           }
        }

        // there should never be anything left in the divisor
        // aka divisor = 1
        // TODO check for that
        unsigned long long f = 1ULL;
        for(auto p: dividend ) {
            unsigned long long pf = p.first;
            int count = p.second;
            for(int i = 1; i <= count; ++i) {
                f = f * pf;
            }
        }

        return f;
    }

    bool can_make(string& str, int s, int e, unsigned long long k) {
        // dividend
        int l = e-s+1;
        if( l == 1 )
            return k == 1;
        unordered_map<int,int> dividend;
        for(int j = 2; j <= l; ++j) {
            for(auto pf: pfs[j])
                dividend[pf.first] += pf.second;
        }

        // divisor
        // TODO we could have a prefixsum[nhalf+1][26] to speed this up
        int _cnt[26];memset(_cnt,0,sizeof _cnt);
        for(int i = e; i >= s; --i)
            ++_cnt[str[i]-'a'];
        unordered_map<int,int> divisor;
        for(int i = 0; i < 26; ++i) {
            if( _cnt[i] < 2 )
                continue;
            for(int j = 2; j <= _cnt[i]; ++j)
                for(auto pf: pfs[j])
                    divisor[pf.first] += pf.second;
        }

        // solve
        for(int j = 2; j < 5000; ++j) { // largest prime factor 4999
            if( dividend.find(j) == dividend.end() || divisor.find(j) == divisor.end() )
                continue;

            if( dividend[j] == divisor[j] ) {
                dividend.erase(j);
                divisor.erase(j);
            } else if( dividend[j] > divisor[j] ) {
                dividend[j] = dividend[j] - divisor[j];
                divisor.erase(j);
            } else { // dividend[j] < divisor[j]
                divisor[j] = divisor[j] - dividend[j];
                dividend.erase(j);
           }
        }

        // there should never be anything left in the divisor
        // aka divisor = 1
        // TODO check for that
        unsigned long long f = 1ULL;
        for(auto p: dividend ) {
            unsigned long long pf = p.first;
            int count = p.second;
            for(int i = 1; i <= count; ++i) {
                f = f * pf;
                if( f >= k )
                    return true;
            }
        }

        return false;
    }

    // binary search
    int search(int s, int e, string& str, int end, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        auto f = can_make(str, mid, end, k);
        if( f ) {
            // can we do better?
            int t = search(mid+1, e, str, end, k);
            return t != -1 ? t : mid;
        }
        return search(s, mid-1, str, end, k);
    }

public:
    string smallestPalindrome(string s, int k) {
        if( !init ) {
            init = true;
            // prime factorization of 2...5000
            // there are in total 15567 primefactors > 1
            // the greatest prime factor is 4999
            for(int i = 2; i <= 5000; ++i)
                pfs[i] = primeFactors(i);
        }

        // s is a palindrome consisting of lowercase chars
        int n = s.size();
        if( n < 4 )
            return k == 1 ? s : "";

        // if n is odd, we have 1 char with odd count
        // that char goes in the middle

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char chr: s)
            ++cnt[chr-'a'];

        // change s to the 1st lexicographically palindromic permutation
        int odd_chr = -1;
        int l = 0;
        int r = n-1;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] % 2 )
                odd_chr = i;
            while( cnt[i] > 1 ) {
                s[l++] = i + 'a';
                s[r--] = i + 'a';
                cnt[i] -= 2;
            }
        }

        if( n % 2 )
            s[l] = odd_chr + 'a';

        if( k == 1 )
            return s;

        // can we make k permutations?
        int b = 0;
        int e = n/2 - 1;
        if( !can_make(s, b, e, k) )
            return "";

        // we need to start permutating somewhere between 0...e
        b = search(0, e, s, e, k); // cout << "b " << b << endl;

        // collect freq of chars in range b..e
        int freq[26];memset(freq,0,sizeof freq);
        for(int i = b; i <= e; ++i)
            ++freq[s[i]-'a'];

        unsigned long long sum = 0;
        int idx = b; // index in s
        while( sum != k ) {
            sum = 0ULL;
            for(int i = 0; i < 26; ++i) {
                if( freq[i] == 0 )
                    continue;

                // assume we place the char at idx
                --freq[i];

                // calc number of permutation after fixing this char
                unsigned long long xsum = solve(e-idx, freq);
                sum += xsum;

                // if sum > k fix current char and update sum
                // and required kth after fixing char at that position
                if( sum >= k ) {
                    s[idx] = i + 'a';
                    ++idx;
                    k -= (sum - xsum);
                    break;
                }

                // if sum < n, add character back
                if (sum < k)
                    ++freq[i];
            }
        }
        // fill in the rest of s in range idx..e
        for(int i = 25; idx <= e && i >= 0; --i)
            if( freq[i] ) {
                s[idx] = i + 'a';
                ++idx;
                --freq[i];
                ++i; // loop reduces i, but we need to use all chars at i
            }

        // match second half of s to the 1st half range b..e
        int j = e+1;
        if( n % 2 )
            ++j;
        for(int i = e; i >= b; --i, ++j)
            s[j] = s[i];

        return s;
    }
};
