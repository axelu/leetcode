
// 1012. Numbers With Repeated Digits
// https://leetcode.com/problems/numbers-with-repeated-digits/



class Solution {
private:
    // Returns factorial of n
    long long fact(int n) {
	    long long res = 1;
	    for(int i = 2; i <= n; ++i)
		    res = res * (long long)i;
	    return res;
    }

    int nPr(int n, int r) {
        // regular permutations formula P(n,r) = n!/(n-r)!
	    return fact(n) / fact(n - r);
    }

public:
    int numDupDigitsAtMostN(int n) {
        if( n <= 10 )
            return 0;

        /* hint 1 given:
         *     How many numbers with no duplicate digits?
         *     How many numbers with K digits and no duplicates?
         * hint 2 given:
         *     How many numbers with same length as N?
         *     How many numbers with same prefix as N?
         */

        // idea: get count of numbers with no repeated digits
        //       and subtract from n

        vector<int> v; // inidividual digits in n
        int x = n+1;
        while( x > 0) {
            v.push_back(x % 10);
            x /= 10;
        }
        reverse(v.begin(),v.end());

        int t = 0; // count of numbers without duplicate digts

        // number of permutations for all positions
        // except the left most position
        int nbr_digits = v.size();
        for(int i = 1; i < nbr_digits; ++i)
            t += 9 * nPr(9,i-1);

        // left most digit
        int seen[10];memset(seen,0,sizeof seen);
        for(int i = 0; i < nbr_digits; ++i) {
            // we can have digits 0 to digits digits[i]-1
            // example if digit is yy8xxx, we can have
            //     yy0xxx, yy1xxx,..., yy7xxx
            // if we are at i = 0 respectively the left most position
            //     we need to start at 1xxxxxx as we we cannot have a leading 0
            int k = i > 0 ? 0 : 1;
            for(; k < v[i]; ++k) {
                // have we seen k already?
                if( seen[k] )
                    continue;
                // reduce the number of digits we can chose from by i
                // because we already have consumed them, meaning i
                // unique digits are already used in the positions we
                // have passed
                t += nPr(9-i,nbr_digits-i-1);
            }
            // if the current digit is a digit we have already seen,
            // then there is no point in continuing
            if( seen[v[i]] )
                break;
            seen[v[i]] = 1;
        }

        return n - t;
    }
};
