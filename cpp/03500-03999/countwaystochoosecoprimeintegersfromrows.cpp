
// 3725. Count Ways to Choose Coprime Integers from Rows
// https://leetcode.com/problems/count-ways-to-choose-coprime-integers-from-rows/



// initialize ones
int lgcd[151][151];
bool init = false;

class Solution {
private:
    const long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret % mod;
    }

    long m, n;
    vector<int> ones;

    long mem[151][151];

    long rec(vector<vector<int>>& mat, int i, int _gcd) {
        // the gcd so far is _gcd
        // we are in row i

        if( mem[i][_gcd] != -1L )
            return mem[i][_gcd];

        int rem_rows = m - i; // remaining rows inclusive of row i

        // handle _gcd == 1
        if( _gcd == 1 )
            return mem[i][_gcd] = modular_pow(n, rem_rows);

        long ret = 0L;

        // handle last row, more formaly i == m-1
        // including 1's in last row
        if( i == m-1 ) {
            ret = (long)ones[i];
            for(int j = ones[i]; j < n; ++j) {
                if( lgcd[_gcd][mat[i][j]] == 1 )
                    ++ret;
            }
            return mem[i][_gcd] = ret % mod;
        }

        // handle mat[i][j] == 1
        ret = ((long)ones[i] * modular_pow(n, rem_rows-1)) % mod;

        // handle mat[i][j] != 1
        for(int j = ones[i]; j < n; ++j) {
            int _gcd_new = lgcd[_gcd][mat[i][j]];
            ret = (ret + rec(mat, i+1, _gcd_new)) % mod;
        }

        return mem[i][_gcd] = ret;
    }

public:
    int countCoprime(vector<vector<int>>& mat) {
        // TODO we could precalc also our modular_pow
        //     as we know range for base and exponent
        if( !init ) {
            for(int i = 1; i <= 150; ++i)
                for(int j = 1; j <= 150; ++j)
                    lgcd[i][j] = gcd(i,j);

            init = true;
        }

        // 1 <= m,n <= 150
        // 1 <= mat[i][j] <= 150
        m = mat.size();    // rows
        n = mat[0].size(); // cols

        // edge case
        if( m == 1 ) {
            int res = 0;
            for(int j = 0; j < n; ++j)
                if( mat[0][j] == 1 )
                    ++res;
            return res;
        }

        // the order in a given row does not matter
        // let us sort each row and note number of 1s in each row
        ones.assign(m,0);
        for(int i = 0; i < m; ++i) {
            sort(begin(mat[i]), end(mat[i]));
            // find left j where mat[i][j] > 1

            // returns 'n' if mat[i][n-1] <= target
            // returns  0  if mat[i][0] > target
            // binary search upper bound while loop
            // upper bound -> greater than target
            int s = 0;
            int e = n; // n = nums.size()
            int mid;
            int target = 1;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( target >= mat[i][mid] )
                    s = mid + 1;
                else
                    e = mid;
            }
            if( s < n && mat[i][s] <= target )
                ++s;

            ones[i] = s;
        }

        long ans = 0L;
        memset(mem,-1,sizeof mem);
        for(int j = 0; j < n; ++j)
            ans = (ans + rec(mat, 1, mat[0][j])) % mod;

        return ans;
    }
};
