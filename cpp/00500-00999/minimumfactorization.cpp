
// 625. Minimum Factorization
// https://leetcode.com/problems/minimum-factorization/



/* INT_MAX 2147483647
 *
 */
class Solution {
private:
    // prime factorization
    bool primeFactors(int n, vector<int>& ret) {
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
        for(int i = 3; i <= sqrt(n); i = i + 2) {
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
    int smallestFactorization(int num) {
        if( num == 1 || num == 2 || num == 3 || num == 5 || num == 7 )
            return num;

        // get prime factors of num
        // if there is a prime factor > 7, then we don't have a solution
        // otherwise combine 3x3 -> 9 as often as we can
        // then combine 2x2x2 -> 8 as often as we can
        // then combine 2x3 -> 6 as often as we can
        // then combine 2x2 -> 4 as often as we can
        vector<int> pfs(8,0);
        bool f = primeFactors(num,pfs);
        if( !f )
            return 0;

        priority_queue<int,vector<int>,greater<int>> pq;
        while( pfs[3] >= 2 ) {
            pq.push(9);
            pfs[3] -= 2;
        }
        while( pfs[2] >= 3 ) {
            pq.push(8);
            pfs[2] -= 3;
        }
        while( pfs[2] >=1 && pfs[3] >= 1 ) {
            pq.push(6);
            --pfs[3];
            --pfs[2];
        }
        while( pfs[2] >= 2 ) {
            pq.push(4);
            pfs[2] -= 2;
        }
        while( pfs[3] >= 1 ) {
            pq.push(3);
            --pfs[3];
        }
        while( pfs[2] >= 1 ) {
            pq.push(2);
            --pfs[2];
        }
        while( pfs[5] >= 1) {
            pq.push(5);
            --pfs[5];
        }
        while( pfs[7] >= 1 ) {
            pq.push(7);
            --pfs[7];
        }

        if( pq.size() > 10 )
            return 0;

        long ans = 0;
        while( !pq.empty() && ans <= INT_MAX ) {
            ans = 10 * ans + pq.top();
            pq.pop();
        }

        return ans <= INT_MAX ? ans : 0;
    }
};
