
// Maximum Non Negative Product in a Matrix
// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/

// NOTE: initial Time Limit Exceeded (TLE) error
// the real solution is dynamic programming with two matrixes,
// one for min and one for max values to account for alternating
// - and + values.
// see here for a good example
// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/discuss/855082/C%2B%2B-Dynamic-Programming-With-Comments
//
// below is Brute Force approach that with pre-processig of the
// last row and last column passes the TLE error
// NOTE that the DFS method I started on, but abonded it, so that one is unfinished


#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>



using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        _mend = grid.size();
        _nend = grid[0].size();
        const long long int m = 1000000007; // Modulo 10^9+7 = 1000000007

        _end = grid[_mend - 1][_nend - 1];
        if( _end == 0 ) return 0;

        // brute force -> TLE error
        _p = LLONG_MIN;
        // pre-processing last row
        vector<long long int> lrf(_nend);
        lrf[_nend - 1] = _end;
        for(int i = _nend - 2; i >=0; --i) {
            lrf[i] = lrf[i + 1] * grid[_mend - 1][i];
        }
        // pre-processing last column
        vector<long long int> lcf(_mend);
        lcf[_mend - 1] = _end;
        for(int i = _mend - 2; i >=0; --i) {
            lcf[i] = lcf[i + 1] * grid[i][_nend - 1];
        }
        _bf(0,0,1,grid, lrf, lcf);

        if( _p < 0 ) {
            return -1;
        } else if ( _p == 0 ) {
            return 0;
        } else {
            return _p % m;
        }

    }
private:
    long long int _p;
    long long int _end;
    int _mend;
    int _nend;

    void _bf(int m, int n, long long int f, vector<vector<int>>& grid,
        vector<long long int>& lrf, vector<long long int>& lcf) {
        // cout << "m " << m << " n " << n << endl;

        // outside
        if( m == _mend || n == _nend )
            return;

        long long int t = grid[m][n];

        // 0 along the path
        if( t == 0 ) {
            _p = max(_p, (long long int) 0);
            return;
        }

        // last row
        if( m == _mend - 1 ) {
                // cout << "lrf ";
                // for(auto i : lrf) cout << i << " ";
                // cout << endl;
                if (( f < 0 && lrf[n] > 0 ) || ( f > 0 && lrf[n] < 0)) {
                    _p = max(_p, (long long int) -1);
                } else {
                    long long int c = f * lrf[n];
                    // cout << "t " << t << endl;
                    _p = max(_p, c);
                }
                return;

        }

        // last column
         if( n == _nend - 1 ) {
                // cout << "lcf ";
                // for(auto i : lcf) cout << i << " ";
                // cout << endl;
                if (( f < 0 && lcf[m] > 0 ) || ( f > 0 && lcf[m] < 0)) {
                    _p = max(_p, (long long int) -1);
                } else {
                    long long int c = f * lcf[m];
                    // cout << "t " << t << endl;
                    _p = max(_p, c);
                }
                return;

        }

        // down
        _bf(m + 1, n, f * grid[m][n], grid, lrf, lcf);
        // right
        _bf(m, n + 1, f * grid[m][n], grid, lrf, lcf);
    }

    long long int _dfs(int m, int n, vector<vector<int>>& grid,
        unordered_map<int,unordered_map<int,long long int>> mem) {
        // cout << "m " << m << " n " << n << endl;

        // outside
        if( m == _mend || n == _nend )
            return 1;

        // 0 along the path
        if( grid[m][n] == 0 ) {
            return 0 ;
        }

        // been here?
        auto fm = mem.find(m);
        if( fm != mem.end() ) {
            auto fn = fm->second.find(n);
            if( fn != fm->second.end() ) {
                return fn->second;
            }
        }

        // down
        long long int d = _dfs(m + 1, n, grid, mem);
        // right
        long long int r = _dfs(m, n + 1, grid, mem);

        long long int t = grid[m][n];
        long long int ret;
        long long int dret;
        long long int lret;
        if( d == 0 ) {
            dret = 0;
        } else if ( ( t < 0 && d > 0 ) || ( t > 0 && d < 0 ) ) {
            dret = -1;
        } else {
            dret = t * d;
        }

        return ret;
    }
};


int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    Solution s;
    vector<vector<int>> grid;

    cout << "{{-1,-2,-3},{-2,-3,-3},{-3,-3,-2}}" << endl;
    grid = {{-1,-2,-3},{-2,-3,-3},{-3,-3,-2}};
    // cout << s.maxProductPath(grid) << endl;
    assert(s.maxProductPath(grid) == -1);

    cout << "{{1,-2,1},{1,-2,1},{3,-4,1}}" << endl;
    grid = {{1,-2,1},{1,-2,1},{3,-4,1}};
    // cout << s.maxProductPath(grid) << endl;
    assert(s.maxProductPath(grid) == 8);

    cout << "{{1,3},{0,-4}}" << endl;
    grid = {{1,3},{0,-4}};
    // cout << s.maxProductPath(grid) << endl;
    assert(s.maxProductPath(grid) == 0);

    cout << "{{1,4,4,0},{-2,0,0,1},{1,-1,1,1}}" << endl;
    grid = {{1,4,4,0},{-2,0,0,1},{1,-1,1,1}};
    // cout << s.maxProductPath(grid) << endl;
    assert(s.maxProductPath(grid) == 2);

    // time limit exceeded (TLE) error with brute force approach,
    // result 93410601 is correct
    // m = 15, n = 15
    // case 158/159
    cout << "{1,-3,-1,-1,4,-4,-4,-4,-1,3,-1,0,4,-2,-2},{..." << endl;
    grid = {{1,-3,-1,-1,4,-4,-4,-4,-1,3,-1,0,4,-2,-2},{-3,-2,-4,3,3,2,4,0,-1,2,-4,3,1,2,-2},{0,-4,0,4,1,3,1,4,-4,-2,-2,-4,-1,-4,2},{-1,-4,-1,-2,-1,-4,-2,3,3,0,0,-1,-1,-3,0},{-4,0,2,-1,0,2,3,-1,3,-3,3,3,-3,2,4},{3,-1,-4,3,-2,-4,-1,4,-4,0,3,4,-1,4,-3},{3,-3,-3,2,4,-4,-4,0,2,-2,-3,0,2,-1,-4},{0,-2,0,-2,2,-3,2,-3,4,0,1,0,-1,4,-3},{-4,-1,3,-3,2,4,3,4,1,-3,1,1,0,-2,-3},{3,-3,4,-1,-3,4,1,-1,1,2,0,-4,0,0,1},{-4,0,-4,-2,-2,0,4,-1,2,-1,-2,-1,1,0,-1},{-4,-3,-3,3,3,4,3,1,-1,-4,-3,2,3,-2,-3},{1,4,-2,-4,-2,-1,1,0,2,-4,4,-1,2,-1,0},{0,-1,3,-3,0,-3,2,-2,0,-2,-4,-2,2,-4,4},{1,-2,-1,-3,-3,0,-2,0,1,4,-1,-2,-4,-4,4}};

    start = chrono::system_clock::now();

    s.maxProductPath(grid);

    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    assert(s.maxProductPath(grid) == 93410601);

    return 0;
}
