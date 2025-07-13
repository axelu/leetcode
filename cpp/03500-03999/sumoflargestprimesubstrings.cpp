
// 3556. Sum of Largest Prime Substrings
// https://leetcode.com/problems/sum-of-largest-prime-substrings/





class Solution {
private:
    bool isPrime(long n) {
        if( n == 2L || n == 3L )
            return true;

        if( n <= 1L || n % 2L == 0L || n % 3L == 0L  )
            return false;

        for(long i = 5L; i * i <= n; i += 6L ) {
            if( n % i == 0L || n % (i + 2L) == 0L )
                return false;
        }

        return true;
    }

public:
    long long sumOfLargestPrimes(string s) {
        int n = s.size(); // 1 <= s.length <= 10

        //                  0123456789
        // largest possible 9999999999

        set<long> st;

        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' )
            continue;

            long p = 0L;
            for(int j = i; j < n; ++j) {
                p = p * 10L + (long)(s[j]-'0');

                // TODO check if already seen, if so skip

                if( isPrime(p) )
                    st.insert(p);
            }
        }

        long long ans = 0;
        int cnt = 0;
        for(auto itr = st.rbegin(); itr != st.rend() && cnt < 3; ++itr) {
            ans += *itr;
            ++cnt;
        }

        return ans;
    }
};
