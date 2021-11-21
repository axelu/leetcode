
// 1626. Best Team With No Conflicts
// https://leetcode.com/problems/best-team-with-no-conflicts/


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
    set<int> us;        // unique scores
    int sid[1000001];   // score idx
    int dp[1001][1000]; // max by score(idx) and position

    int bestTeamScore(int score, int i, const int& n, vector<vector<int>>& aands) {
        if( i >= n ) return 0;
        if( dp[sid[score]][i] != -1 ) return dp[sid[score]][i];

        // current player
        int cpscore = aands[i][1];

        // advance as long as players' score does not change
        int k = i + 1;
        int t = cpscore;
        while( k < n && aands[k][1] == cpscore ) {
            t += cpscore;
            ++k;
        }

        // take current player(s) if possible
        int a = 0;
        if( cpscore >= score )
            a = t + bestTeamScore(cpscore,k,n,aands);

        // skip current player(s)
        int b = bestTeamScore(score,k,n,aands);

        return dp[sid[score]][i] = max(a,b);
    }
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        // 1 <= scores.length, ages.length <= 1000
        // scores.length == ages.length
        // 1 <= scores[i] <= 10e6
        // 1 <= ages[i] <= 1000
        auto n = scores.size();
        if( n == 1 ) return scores[0];

        // conflict if younger player has strictly higher score than older player
        // conflict does not occur between players of the same age

        vector<vector<int>> aands; // age and score
        us.clear();
        us.insert(0); // unique scores
        for(int i = 0; i < n; ++i) {
            aands.push_back({ages[i],scores[i]});
            us.insert(scores[i]);
        }
        sort(begin(aands),end(aands)); // sorts same age w/ higher score properly
        // for(int i = 0; i < n; ++i)
        //     cout << aands[i][0] << " " << aands[i][1] << "; ";
        // cout << endl;

        // transform set of unique scores into a score index
        int k = 0;
        for(auto it = begin(us); it != end(us); ++it) {
            sid[*it] = k;
            ++k;
        }

        // init dp
        for(int i = 0; i < us.size(); ++i)
            for(int j = 0; j < n; ++j)
                dp[i][j] = -1;

        return bestTeamScore(0,0,n,aands);
    }

    int bestTeamScore2(vector<int>& scores, vector<int>& ages) {
        // 1 <= scores.length, ages.length <= 1000
        // scores.length == ages.length
        // 1 <= scores[i] <= 10e6
        // 1 <= ages[i] <= 1000
        int n = scores.size();
        if( n == 1 ) return scores[0];

        vector<vector<int>> aands;
        for(int i = 0; i < n; ++i)
            aands.push_back({ages[i], scores[i]});
        sort(aands.begin(), aands.end(), greater<>()); // sorts same age w/ higher score properly

        int r = 0;
        int dp[n];
        for(int i = 0; i < n; ++i) {
            int cpscore = aands[i][1];  // current player ith's score
            dp[i] = cpscore;            // include current player i
            for(int j = 0; j < i; ++j)
                if( aands[j][1] >= aands[i][1]) // add other players up to player i with same or higher score
                    dp[i] = max(dp[i], dp[j] + cpscore);

            r = max(r, dp[i]);
        }

        return r;
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
    vector<int> scores;
    vector<int> ages;
    int r;

    // Example 1
    scores = {1,3,5,10,15};
    ages = {1,2,3,4,5};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(34 == r);

    // Example 2
    scores = {4,5,6,5};
    ages = {2,1,2,1};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(16 == r);

    // Example 2a
    scores = {6,5,4,5};
    ages = {2,1,2,1};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(16 == r);

    // Example 3
    scores = {1,2,3,5};
    ages = {8,9,10,1};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(6 == r);

    // Example Axel 1
    scores = {6,4,5,5};
    ages = {1,1,2,2};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(14 == r);

    // Example Axel 2
    scores = {6,4,5,5,6,6};
    ages = {1,1,2,2,2,2};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(26 == r);

    // Example Axel 3
    scores = {6,4,6,6};
    ages = {1,1,2,2};
    r = s.bestTeamScore(scores,ages);
    cout << "result " << r << endl;
    assert(22 == r);

    // Example Axel 4
    scores = {};
    ages = {};
    for(int i = 1; i <= 1000; ++i) {
        scores.push_back(i);
        ages.push_back(i);
    }

    start = chrono::system_clock::now();
    r = s.bestTeamScore(scores,ages);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result " << r << endl;
    assert(500500 == r);
    // for(int i = 1; i <= 1000; ++i) cout << i << ",";
    // cout << endl;

    start = chrono::system_clock::now();
    r = s.bestTeamScore2(scores,ages);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result " << r << endl;
    assert(500500 == r);

    return 0;
}
