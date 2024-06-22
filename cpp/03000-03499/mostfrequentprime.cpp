
// 3044. Most Frequent Prime
// https://leetcode.com/problems/most-frequent-prime/




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


    map<int,int> cnt;

    // 8 directions R RD D  LD L  LU U  RU
    const int dirR[8] = { 0, 1, 1, 1, 0,-1,-1,-1};
    const int dirC[8] = { 1, 1, 0,-1,-1,-1, 0, 1};

    void explore(const vector<vector<int>>& mat, const int m, const int n, const int i, const int j, const int k) {
        int p = mat[i][j];

        int i_new = i + dirR[k];
        int j_new = j + dirC[k];
        while( i_new >= 0 && i_new < m && j_new >= 0 && j_new < n ) {
            p *= 10;
            p += mat[i_new][j_new];
            if( isPrime(p) )
                ++cnt[p];
            i_new += dirR[k];
            j_new += dirC[k];
        }

        return;
    }


public:
    int mostFrequentPrime(vector<vector<int>>& mat) {
        int m = mat.size();     // 1 <= m <= 6
        int n = mat[0].size();  // 1 <= n <= 6

        // worst case m = 6 and n = 6 -> 36 cells
        // that will make for 160 directions to be explored
        // 16 cells * 8 directions (the 4x4 inner square)
        //  4 cells * 3 directions (the 4 corners)
        // 16 cells * 5 directions ( the outer cells except the 4 corner cells)
        // longest path is 6 -> if all are digit 9, then our largest number is 999999
        // number of primes less than 1,000,000: 78,498

        for(int i = 0; i < m; ++i) {            // row
            for(int j = 0; j < n; ++j) {        // col
                for(int k = 0; k < 8; ++k) {    // direction
                    explore(mat, m, n, i, j, k);
                }
            }
        }

        int mx = 0;
        int p = -1;

        for(auto& primecount: cnt) {
            if( primecount.second >= mx ) {
                mx = primecount.second;
                p = primecount.first;
            }
        }

        return p;
    }
};
