
// 2906. Construct Product Matrix
// https://leetcode.com/problems/construct-product-matrix/





class Solution {
/* from the hint: Try to solve this without using the '/' (division operation).
 *                Create two 2D arrays for suffix and prefix product, and use them to find the product for each position.
 *
 *                 0  1  2  3
 * example         1  2  3  4  -> product of all elements = 24
 * prefixProduct   1  1  2  6
 * suffixProduct  24 12  4  1
 * answer         24 12  8  6
 * answer[i] = prefixProduct[i] * suffixProduct[i]
 */

public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int m = grid.size();        // rows
        int n = grid[0].size();     // cols

        long mod = 12345L;

        if( m == 1 && n == 1 ) {
            int t = grid[0][0] % mod;
            return {{t}};
        }

        long prefixProduct[m*n];
        prefixProduct[0] = 1L;
        for(int k = 1; k < m*n; ++k) {
            int t = k-1;
            int i = t / n;
            int j = t % n;
            prefixProduct[k] = (prefixProduct[k-1] * (grid[i][j] % mod)) % mod;
        }
        //for(int k = 0; k < m*n; ++k)
        //    cout << k << ":" << prefixProduct[k] << " ";
        //cout << endl;

        long suffixProduct[m*n];
        suffixProduct[m*n-1] = 1L;
        for(int k = m*n-2; k >= 0; --k) {
            int t = k+1;
            int i = t / n;
            int j = t % n;
            suffixProduct[k] = (suffixProduct[k+1] * (grid[i][j] % mod)) % mod;
        }
        //for(int k = 0; k < m*n; ++k)
        //    cout << k << ":" << suffixProduct[k] << " ";
        //cout << endl;

        vector<vector<int>> p(m,vector<int>(n));
        for(int k = 0; k < m*n; ++k) {
            int kp = (prefixProduct[k] * suffixProduct[k]) % mod;
            int i = k / n;
            int j = k % n;
            p[i][j] = kp;
        }

        return p;
    }
};
