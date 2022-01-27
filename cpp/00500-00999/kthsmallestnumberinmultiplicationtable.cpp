
// 668. Kth Smallest Number in Multiplication Table
// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
// day 16 November 2021 challenge




class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

    array<int,2> solve(int m, int n, int x) {
        // if x is a prime, x will only be in
        // our table if m >= x || n >= x
        // don't call with that here!

        int cntSmaller = 0;
        int cntEqual   = 0;
        for(int i = 1; i <= min(m,x); ++i) {
            int t = x/i;
            if( x%i == 0 ) {
                cntSmaller += min(t-1,n);
                if( t <=n )
                    ++cntEqual;
            } else {
                cntSmaller += min(t,n);
            }
        }
        return {cntSmaller+1,cntSmaller+cntEqual};
    }


    // binary search
    int search(int m, int n, int s, int e, int k) {
        // cout << "search s " << s << " e " << e << endl;

        int mid = s +((e-s)/2);
        // cout << "  mid " << mid << endl;
        // how many numbers are there smaller than mid
        // and how many times do each of these occur
        // and how many times does mid itself occur
        // if mid is a prime, mid will only be in
        // our table if m >= mid || n >= mid
        // Note: 2 and 3 are the only consecutive primes
        if( isPrime(mid) && m < mid && n < mid ) {
            if( mid == s )
                ++mid;
            else
                --mid;
        }

        array<int,2> range = solve(m,n,mid);
        if( range[0] <= k && range[1] >= k) {
            return mid;
        } else if( k < range[0] ) {
            return search(m,n,s,mid-1,k);
        } else {
            // k > range[1]
            return search(m,n,mid+1,e,k);
        }
    }


public:
    int findKthNumber(int m, int n, int k) {
        // 1 <= m, n <= 3 * 10^4
        // 1 <= k <= m * n

        if( k == 1 )
            return 1;
        if( k == m*n )
            return m*n;
        if( m == 1 || n == 1 )
            return k;

        // we know that the answer is between 1 and m*n inclusive
        return search(m,n,1,m*n,k);
    }
};
