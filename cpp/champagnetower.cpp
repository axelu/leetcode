
// Champagne Tower
// day 26 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/562/week-4-october-22nd-october-28th/3508/
// https://leetcode.com/problems/champagne-tower/




#include <iostream>
#include <cassert>
#include <chrono>

#include <stack>
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
#include <climits>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        // 0 <= poured <= 10e9 cups
        // 0 <= query_glass <= query_row < 100
        // glass and row 0 indexed
        // one glass holds 1 cup

        // base case
        if( query_row == 0 && query_glass == 0 )
            return poured >= 1 ? 1.00000 : 0.00000;

        double dp[101][101]; // dp[row][glass], 0 indexed
        dp[0][0] = (double)poured;

        double r;
        for(int i = 1; i <= query_row + 1; ++i) {
            for(int j = 0; j <= i; ++j) {
                r = 0.00000;

                // up and left
                if( j-1 >= 0 && dp[i-1][j-1] >= 1.00000 ) {
                    r = (dp[i-1][j-1]-1.00000)/2.00000;
                    dp[i-1][j-1] = 1.00000;
                }
                // up and right
                if( j < i && dp[i-1][j] >= 1.00000 )
                    r += (dp[i-1][j]-1.00000)/2.00000;

                dp[i][j] = r;
            }
        }

        return dp[query_row][query_glass];
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    int poured;
    int query_row;
    int query_glass;
    double r;

    // Exmple 1
    cout << "Example 1" << endl;
    poured = 1;
    query_row = 1;
    query_glass = 1;
    r = s.champagneTower(poured,query_row,query_glass);
    cout << "result " << r << endl;
    assert(0.00000 == r);

    // Exmple 2
    cout << "Example 2" << endl;
    poured = 2;
    query_row = 1;
    query_glass = 1;
    r = s.champagneTower(poured,query_row,query_glass);
    cout << "result " << r << endl;
    assert(0.50000 == r);

    // Exmple 3
    cout << "Example 3" << endl;
    poured = 100000009;
    query_row = 33;
    query_glass = 17;
    r = s.champagneTower(poured,query_row,query_glass);
    cout << "result " << r << endl;
    assert(1.00000 == r);

    // TODO edge case poured 1000000000, query_row 100, query_glass 99
    // 1262500
    // 99
    // 49  or 50 answer 1.00000




    return 0;
}
