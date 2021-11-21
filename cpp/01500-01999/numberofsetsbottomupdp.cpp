
// 1621. Number of Sets of K Non-Overlapping Line Segments
// https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/



#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>
#include <bitset>
#include <cstring>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int numberOfSets(int n, int k) {
        // 2 <= n <= 1000
        // 1 <= k <= n-1

        // Bottom Up DP implementation

        long dp[1001][1000];
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= k; ++j)
                dp[i][j] = j == i - 1 ? 1L : 0L;

        int j, jmax;
        long r;
        long mod = 1000000007;
        int x = n - k + 1; // used to calculate min column
        for(int i = 3; i <= n; ++i) {
            jmax = i - 1 < k ? i - 1 : k;
            j = i <= x ? 1 : 1 + i - x;
            for(; j <= jmax; ++j) {
                if( j == 1 ) {
                    r = (i*(i-1))/2;
                } else {
                    r = dp[i-1][j] % mod;
                    r = r + (dp[i-2][j] % mod);
                    r = r + (dp[i-1][j-1] % mod);
                    r = r + (dp[i-2][j-1] % mod);
                    r = r - (dp[i-3][j] % mod);
                    r %= mod;
                    if( r < 0 ) r += mod;
                }
                dp[i][j] = r;
            }
        }

        return dp[n][k];
    }
};

int main() {

    Solution s;
    int n;
    int k;
    int r;

    // Example 1
    n = 4;
    k = 2;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(5 == r);

    // Example
    n = 8;
    k = 3;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(210 == r);

    // Example 2
    n = 3;
    k = 1;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(3 == r);

    // Example 3
    n = 30;
    k = 7;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(796297179 == r);

    // Example 4
    n = 5;
    k = 3;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(7 == r);

    // Example 5
    n = 3;
    k = 2;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(1 == r);

    // edge cases
    // n 2 k 1
    n = 2;
    k = 1;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(1 == r);
    // n 1000 k 1
    n = 1000;
    k = 1;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(499500 == r);
    // n 1000 k 999
    n = 1000;
    k = 999;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(1 == r);
    // n 1000 k 998
    n = 1000;
    k = 998;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(1997 == r);

    // n 33 k 20
    // initially signed integer overflow error (case 35 / 68)
    n = 33;
    k = 20;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    // assert(1997 == r);

    // n 108 k 6
    // initially wrong answer (case 67 / 68)
    n = 108;
    k = 6;
    cout << "n " << n << " k " << k << endl;
    r = s.numberOfSets(n,k);
    cout << "r " << r << endl;
    assert(405818833 == r);


    return 0;
}
