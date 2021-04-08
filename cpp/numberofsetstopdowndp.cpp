
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
private:
    long dp[1001][1000];
    long mod = 1000000007;

    long f(int n, int k) {
        if( k >= n ) return 0;
        if( dp[n][k] ) return dp[n][k];

        long r;
        if( k == 1 ) {
            r = (n*(n-1))/2;
        } else {
            r = f(n-1,k) % mod;
            r = r + (f(n-2,k) % mod);
            r = r + (f(n-1,k-1) % mod);
            r = r + (f(n-2,k-1) % mod);
            r = r - (f(n-3,k) % mod);
            r %= mod;
            if( r < 0 ) r += mod;
        }

        return dp[n][k] = r;
    }
public:
    int numberOfSets(int n, int k) {
        // 2 <= n <= 1000
        // 1 <= k <= n-1

        // Top Down DP implementation

        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= k; ++j)
                dp[i][j] = j == i - 1 ? 1L : 0L;

        return f(n,k);
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
    assert(379405428 == r);

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
