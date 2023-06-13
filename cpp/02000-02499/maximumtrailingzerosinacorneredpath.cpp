
// 2245. Maximum Trailing Zeros in a Cornered Path
// https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/



/* from the hints:
 *   What actually tells us the trailing zeros of the product of a path?
 *   It is the sum of the exponents of 2 and sum of the exponents of 5
 *   of the prime factorizations of the numbers on that path. The smaller of the two is the answer for that path.
 *   see for a good resource
 *   https://byjus.com/question-answer/the-sum-of-the-exponents-of-the-prime-factors-in-the-prime-factorisation-of-196/
 */

class Solution {
private:
    // prime factorization
    // only return the count of exponents 2 and 5
    pair<int,int> primeFactors(int n) {
        int cnt2 = 0;
        int cnt5 = 0;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++cnt2;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        // for(int i = 3; i <= sqrt(n); i = i + 2) {
        for(int i = 3; i <= sqrt(n) && i <= 5; i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                if( i == 5 )
                    ++cnt5;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        // if( n > 2 )
        //    cout << n << " ";
        if( n == 5 )
            ++cnt5;

        return {cnt2,cnt5};
    }

public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size();     // rows
        int n = grid[0].size();  // cols

        int ans = 0;

        int exp2[m][n];
        int exp5[m][n];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                auto p = primeFactors(grid[i][j]);
                exp2[i][j] = p.first;
                exp5[i][j] = p.second;
            }
        }

        // prefixSum Row for exp2 and exp5
        int prefixSumRexp2[m][n+1];
        int prefixSumRexp5[m][n+1];
        for(int i = 0; i < m; ++i) {
            prefixSumRexp2[i][0] = 0;
            prefixSumRexp5[i][0] = 0;
            for(int j = 1; j <= n; ++j) {
                prefixSumRexp2[i][j] = prefixSumRexp2[i][j-1] + exp2[i][j-1];
                prefixSumRexp5[i][j] = prefixSumRexp5[i][j-1] + exp5[i][j-1];
            }
            int t = min(prefixSumRexp2[i][n],prefixSumRexp5[i][n]);
            ans = max(ans,t);
        }

        // prefixSum Col for exp2 and exp5
        int prefixSumCexp2[n][m+1];
        int prefixSumCexp5[n][m+1];
        for(int j = 0; j < n; ++j) {
            prefixSumCexp2[j][0] = 0;
            prefixSumCexp5[j][0] = 0;
            for(int i = 1; i <= m; ++i) {
                prefixSumCexp2[j][i] = prefixSumCexp2[j][i-1] + exp2[i-1][j];
                prefixSumCexp5[j][i] = prefixSumCexp5[j][i-1] + exp5[i-1][j];
            }
            int t = min(prefixSumCexp2[j][m],prefixSumCexp5[j][m]);
            ans = max(ans,t);
        }

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {


                if( i == 0 && (j == 0 || j == n-1) ) { // top left corner, top right corner
                    int e2 = prefixSumRexp2[i][n] + (prefixSumCexp2[j][m] - prefixSumCexp2[j][i+1]);
                    int e5 = prefixSumRexp5[i][n] + (prefixSumCexp5[j][m] - prefixSumCexp5[j][i+1]);
                    int t = min(e2,e5);
                    ans = max(ans,t);

                } else if( i == m-1 && (j == 0 || j == n-1) ) { // bottom left corner, bottom right corner
                    int e2 = prefixSumRexp2[i][n] + prefixSumCexp2[j][i];
                    int e5 = prefixSumRexp5[i][n] + prefixSumCexp5[j][i];
                    int t = min(e2,e5);
                    ans = max(ans,t);

                } else if( i == 0 || i == m-1 ) { // row 0 OR row m-1
                    int e2 = prefixSumCexp2[j][m] + prefixSumRexp2[i][j];
                    int e5 = prefixSumCexp5[j][m] + prefixSumRexp5[i][j];
                    int t = min(e2,e5);
                    ans = max(ans,t);

                    e2 = prefixSumCexp2[j][m] + (prefixSumRexp2[i][n] - prefixSumRexp2[i][j+1]);
                    e5 = prefixSumCexp5[j][m] + (prefixSumRexp5[i][n] - prefixSumRexp5[i][j+1]);
                    t = min(e2,e5);
                    ans = max(ans,t);

                } else  if( j == 0 || j == n-1 ) { // column 0 OR column n-1
                    int e2 = prefixSumRexp2[i][n] + prefixSumCexp2[j][i];
                    int e5 = prefixSumRexp5[i][n] + prefixSumCexp5[j][i];
                    int t = min(e2,e5);
                    ans = max(ans,t);

                    e2 = prefixSumRexp2[i][n] + (prefixSumCexp2[j][m] - prefixSumCexp2[j][i+1]);
                    e5 = prefixSumRexp5[i][n] + (prefixSumCexp5[j][m] - prefixSumCexp5[j][i+1]);
                    t = min(e2,e5);
                    ans = max(ans,t);

                } else {
                    int e2 = prefixSumCexp2[j][i+1] + prefixSumRexp2[i][j];
                    int e5 = prefixSumCexp5[j][i+1] + prefixSumRexp5[i][j];
                    int t = min(e2,e5);
                    ans = max(ans,t);

                    e2 = prefixSumCexp2[j][i+1] + (prefixSumRexp2[i][n] - prefixSumRexp2[i][j+1]);
                    e5 = prefixSumCexp5[j][i+1] + (prefixSumRexp5[i][n] - prefixSumRexp5[i][j+1]);
                    t = min(e2,e5);
                    ans = max(ans,t);

                    e2 = (prefixSumCexp2[j][m] - prefixSumCexp2[j][i]) + prefixSumRexp2[i][j];
                    e5 = (prefixSumCexp5[j][m] - prefixSumCexp5[j][i]) + prefixSumRexp5[i][j];
                    t = min(e2,e5);
                    ans = max(ans,t);

                    e2 = (prefixSumCexp2[j][m] - prefixSumCexp2[j][i]) + (prefixSumRexp2[i][n] - prefixSumRexp2[i][j+1]);
                    e5 = (prefixSumCexp5[j][m] - prefixSumCexp5[j][i]) + (prefixSumRexp5[i][n] - prefixSumRexp5[i][j+1]);
                    t = min(e2,e5);
                    ans = max(ans,t);
                }
            }
        }

        return ans;
    }
};
