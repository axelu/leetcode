// 62. Unique Paths
// https://leetcode.com/problems/unique-paths/


#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int uniquePaths(int m, int n) {
        if( m == 1 || n == 1 ) return 1;

        // brute force
        // countPath = 0;
        // _bf(0,0,m,n);

        // dynamic programming
        countPath = _dp(m,n);

        return countPath;
    }
private:
    int countPath;

    void _bf(int x, int y, const int m, const int n) {
        if( y < 0 || y == m || x < 0 || x == n ) return;

        if( y == m - 1 && x == n - 1 ) {
            ++countPath;
            return;
        }

        _bf(x + 1, y, m, n); // right
        _bf(x, y + 1, m, n); // down
    }

    int _dp(const int m, const int n) {

        // vector is 0 indexed!!!
        vector<vector<int>> dp(m, vector<int> (n, 1));

        // because our robot can only move down or right, the
        // number of paths to the lower rigth corner is the
        // sum of paths it takes to get to the sqare above and
        // to the sqare to the left
        for(int i = 1; i < m; ++i) {
            for(int k = 1; k < n; ++k) {
                dp[i][k] = dp[i-1][k] + dp[i][k-1];
            }
        }

        return dp[m-1][n-1];
    }
};

int main() {

    Solution s;

    assert(s.uniquePaths(3,7) == 28);
    assert(s.uniquePaths(3,2) == 3);
    assert(s.uniquePaths(7,3) == 28);
    assert(s.uniquePaths(3,3) == 6);

    for(int i = 1; i <= 7; ++i) {
        cout << "i " << i << endl;
        cout << s.uniquePaths(7,i) << endl;
    }



    for(int i = 1; i <= 100; ++i) {
        cout << i << " " << s.uniquePaths(i,100) << endl;
    }

    return 0;
}
