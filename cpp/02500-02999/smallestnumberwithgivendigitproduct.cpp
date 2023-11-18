
// 2847. Smallest Number With Given Digit Product
// https://leetcode.com/problems/smallest-number-with-given-digit-product/





// see also 625. Minimum Factorization https://leetcode.com/problems/minimum-factorization/

class Solution {
private:
    // prime factorization
    bool primeFactors(long long n, vector<int>& ret) {
        // count the number of 2s, 3s, 5s and 7s
        // if prime factor > 7 return an "error", in our case false

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++ret[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2) {
            if( i > 7 )
                return false;
            while(n % i == 0) {
                // cout << i << " ";
                ++ret[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 7 )
            return false;
        if( n > 2 ) {
            // cout << n << " ";
            ++ret[n];
        }

        return true;
    }

public:
    string smallestNumber(long long n) {
        if( n < 10LL )
            return to_string(n);

        vector<int> pfs(8,0);
        bool f = primeFactors(n,pfs);
        if( !f )
            return "-1";

        priority_queue<int,vector<int>,greater<char>> pq;
        while( pfs[3] >= 2 ) {
            pq.push('9');
            pfs[3] -= 2;
        }
        while( pfs[2] >= 3 ) {
            pq.push('8');
            pfs[2] -= 3;
        }
        while( pfs[2] >=1 && pfs[3] >= 1 ) {
            pq.push('6');
            --pfs[3];
            --pfs[2];
        }
        while( pfs[2] >= 2 ) {
            pq.push('4');
            pfs[2] -= 2;
        }
        while( pfs[3] >= 1 ) {
            pq.push('3');
            --pfs[3];
        }
        while( pfs[2] >= 1 ) {
            pq.push('2');
            --pfs[2];
        }
        while( pfs[5] >= 1) {
            pq.push('5');
            --pfs[5];
        }
        while( pfs[7] >= 1 ) {
            pq.push('7');
            --pfs[7];
        }

        string s = "";
        while( !pq.empty() ) {
            s += pq.top();
            pq.pop();
        }


        return s;
    }
};
