
// 1510. Stone Game IV
// day 25 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/562/week-4-october-22nd-october-28th/3507/
// https://leetcode.com/problems/stone-game-iv/




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
    bool winnerSquareGame(int n) {
        // 1 <= n <= 10^5

        // bottom up DP

        // dp[i] to store if first player can win if game starts with i stones
        // 1 win, 0 loose
        // Alice is always the 1st player to take turn
        int dp[n+1];
        for(int i = 0; i < n + 1; ++i)
            dp[i] = -1;
        dp[0] = 0;  // edge case to seed: no stones to take, first player looses

        int j, k;
        for(int i = 1; i <= n; ++i) {
            j = 1;
            k = 1; // k = j * j -> 1 = 1 * 1
            while(k <= i) {
                // new game with i - k stones
                // if there is a scenarios where the first player (now Bob!!!)
                // will lose, it is winnable for Alice -> set dp[i] = 1
                if( dp[i - k] == 0 ) {
                    dp[i] = 1;
                    break;
                }
                ++j;
                k = j * j;
            }
            // there was no scenario for i stones to force second player to loose
            // hence it is NOT winnable for Alice -> set dp[i] = 0
            if( dp[i] == -1 ) dp[i] = 0;
        }

        return dp[n];
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
    int n;
    bool r;

    // Exmple 1
    cout << "Example 1" << endl;
    n = 1;
    r = s.winnerSquareGame(n);
    cout << "result " << r << endl;
    assert(true == r);

    // Exmple 2
    cout << "Example 2" << endl;
    n = 2;
    r = s.winnerSquareGame(n);
    cout << "result " << r << endl;
    assert(false == r);

     // Exmple 3
    cout << "Example 3" << endl;
    n = 4;
    r = s.winnerSquareGame(n);
    cout << "result " << r << endl;
    assert(true == r);

    // Exmple 4
    cout << "Example 4" << endl;
    n = 7;
    r = s.winnerSquareGame(n);
    cout << "result " << r << endl;
    assert(false == r);

    // Exmple 5
    cout << "Example 5" << endl;
    n = 17;
    r = s.winnerSquareGame(n);
    cout << "result " << r << endl;
    assert(false == r);

    return 0;
}
