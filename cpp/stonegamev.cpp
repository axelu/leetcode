
// 1563. Stone Game V
// https://leetcode.com/problems/stone-game-v/

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
private:
    int dp[500][500];
    int sum[500][500];

    int stoneGameV(int s, int e, vector<int>& stoneValue) {
        if( s >= e ) return 0;
        if( dp[s][e] ) return dp[s][e];

        int lrsum = 0;
        int rrsum = sum[s][e];
        int a,b;
        int mx = 0;
        for(int k = s; k < e; ++k) {
            // left row:  s through k
            lrsum += stoneValue[k];
            sum[s][k] = lrsum;
            // right row: k+1 through e
            rrsum -= stoneValue[k];
            sum[k+1][e] = rrsum;

            a = 0;
            b = 0;
            if( lrsum != rrsum ) {
                if( lrsum < rrsum ) {
                    // keep left, discard right
                    a = lrsum + stoneGameV(s,k,stoneValue);
                } else {
                    // keep right, discard left
                    a = rrsum + stoneGameV(k+1,e,stoneValue);
                }
            } else {
                // lrsum == rrsum
                // keep left, discard right
                a = lrsum + stoneGameV(s,k,stoneValue);
                // keep right, discard left
                b = rrsum + stoneGameV(k+1,e,stoneValue);
            }
            mx = max({mx,a,b});
        }

        return dp[s][e] = mx;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        auto n = stoneValue.size();
        if( n == 1 ) return 0;

        // init dp
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dp[i][j] = 0;

        sum[0][n-1] = accumulate(begin(stoneValue),end(stoneValue),0);
        return stoneGameV(0,n-1,stoneValue);
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
    vector<int> stoneValue;
    int r;

    // 1 <= stoneValue.length <= 500
    // 1 <= stoneValue[i] <= 10^6

    stoneValue = {5,5};
    r = s.stoneGameV(stoneValue);
    cout << r << endl;

    return 0;


    srand(time(nullptr));
    int rdm;
    for(int i = 0; i < 500; ++i) {
        rdm = rand() % 1000000 +1;
        stoneValue.push_back(rdm);
    }

    start = chrono::system_clock::now();
    r = s.stoneGameV(stoneValue);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "r " << r << endl;

    for(int i : stoneValue)
        cout << "," << i;
    cout << endl;

    return 0;
}
