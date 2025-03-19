
// 3463. Check If Digits Are Equal in String After Operations II
// https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/






/* multiply it out line by line
 * for a string with size 6, it would result in this
 *         int a = (((((((v[0] + ((4*v[1])%10))%10) + ((6*v[2])%10))%10) + ((4*v[3])%10))%10) + v[4]) %10;
 *         int b = (((((((v[1] + ((4*v[2])%10))%10) + ((6*v[3])%10))%10) + ((4*v[4])%10))%10) + v[5]) %10;
 *         return a == b;
 * we need to find out based on length of s, how many time each element participates in a or b
 * in our example above a: 1*v[0], 4*v[1], 6*v[2], 4*v[3], 1*v[4]
 *                      b: 1*v[1], 4*v[2], 6*v[3], 4*v[4], 1*v[5]
 * the sequence is Pascal's triangle
 * let n be the size of s
 * what we need is the (n-2)th row (0 indexed) of Pascal's triangle
 * https://www.geeksforgeeks.org/find-the-nth-row-in-pascals-triangle/
 * which is basically the binmoial coefficient or number of combinations
 * ((n-2) over k) for all 0 <= k <= n-2 respectively nCr(n-2, k) for all 0 <= k <= n-2
 * and we need it modulus 10, and modulus 10 is a big problem !!! because its not a prime
 *
 * that is how far I got, but I couldnt figure out mod 10
 * for good explanations look here:
 * https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457457/intuitive-pascal-s-triangle-approach-in-c
 * https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457300/easy-to-understand-c-code-using-binomial-coefficients
 * it usess Lucas's theorem and Chinese Remainder theorem
 * https://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/
 * https://cp-algorithms.com/combinatorics/binomial-coefficients.html#binomial-coefficient-modulo-an-arbitrary-number
 */
class Solution {
private:
    // generate nth row in Pascal's triangle
    // https://www.geeksforgeeks.org/find-the-nth-row-in-pascals-triangle/
    // Note: integer overflow for n >= 30
    vector<int> generateNthrow(int n) {
        vector<int> res;

        // nC0 = 1
        int prev = 1;
        res.push_back(prev);

        for (int i = 1; i <= n; i++) {
            // nCr = (nCr-1 * (n - r + 1))/r
            int curr = (prev * (n - i + 1)) / i;
            res.push_back(curr);
            prev = curr;
        }
        return res;
    }

    //-------------------------------------------------------------------------

    int fastExp(int base, int exp, int mod = 10) {
        int result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        } return result;
    }

    const int inv[10] = {1, 1, -1, 7, -1, -1, -1, 3, -1, 9};

    vector<int> generateNthrowMod10(int n) {
        vector<int> res(n + 1, 1);

        int val = 1, two = 0, five = 0;
        for (int k = 1; k < n; ++k) {
            int mult = n - k + 1, div = k, pval = val;
            while (mult && mult % 2 == 0) { mult /= 2; two++; }
            while (mult && mult % 5 == 0) { mult /= 5; five++; }
            while (div && div % 2 == 0) { div /= 2; two--; }
            while (div && div % 5 == 0) { div /= 5; five--; }
            val = (val * (mult ? mult % 10 : 1) * inv[div % 10]) % 10;

            if (two && five) {
                res[k] = 0;
            } else {
                res[k] = val * fastExp(2, two) * fastExp(5, five) % 10;
            }
        }
        return res;
    }

    //-------------------------------------------------------------------------

    int binmod10(int n, int k) {
        int mod2 = binmod2(n, k);
        int mod5 = binmod5(n, k);
        for (int i = 0; i < 10; i++) {
            if (i % 2 == mod2 && i % 5 == mod5)
                return i;
        }
        return 0;
    }

    int binmod2(int n, int k) {
        while (k > 0) {
            if ((k & 1) > (n & 1))
                return 0;
            n >>= 1;
            k >>= 1;
        }
        return 1;
    }

    int binmod5(int n, int k) {
        int res = 1;
        while (n > 0 || k > 0) {
            int nd = n % 5;
            int kd = k % 5;
            if (kd > nd)
                return 0;
            res = (res * binsmall(nd, kd)) % 5;
            n /= 5;
            k /= 5;
        }
        return res;
    }

    int binsmall(int n, int k) {
        if (k > n)
            return 0;
        int fact[5] = {1, 1, 2, 1, 4};
        int numerator = fact[n];
        int denominator = (fact[k] * fact[n - k]) % 5;
        int deninv = 0;
        for (int i = 0; i < 5; i++) {
            if ((denominator * i) % 5 == 1) {
                deninv = i;
                break;
            }
        }
        return (numerator * deninv) % 5;
    }

public:
    bool hasSameDigits(string s) {
        int n = s.size();

        // string to vector<int>
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            v[i] = s[i]-'0';

        // vector<int> r = generateNthrow(n-2); // up to 29 no overflow
        // vector<int> r = generateNthrowMod10(n-2);
        /*
        for(int i = 0; i < r.size(); ++i)
            cout << i << ":" << r[i] << " ";
        cout << endl;
        */

        // alternatively
        vector<int> r(n-1);
        for(int i = 0; i <= n-2; ++i)
            r[i] = binmod10(n-2, i); // nCr_mod10(n-2, i);

        int a = 0;
        for(int i = 0; i < n-1; ++i)
            a = (a + ((v[i] * r[i]) % 10)) % 10;

        int b = 0;
        for(int i = 1; i < n; ++i)
            b = (b + ((v[i] * r[i-1]) % 10)) % 10;

        return a == b;
    }
};
