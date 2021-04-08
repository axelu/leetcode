
// day 4 October 2020 challenge
// Remove Covered Intervals
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3483/
// https://leetcode.com/problems/remove-covered-intervals/

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


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // 1 <= intervals.length <= 1000
        // 0 <= intervals[i][0] < intervals[i][1] <= 10^5
        auto n = intervals.size();
        if( n == 1 ) return 1;

        // Brute Force (only 1000 intervals max)
        int r = 0;
        auto itb = begin(intervals);
        auto ite = end(intervals);
        for(auto ito = itb; ito != ite; ++ito) {
            for(auto iti = itb; iti != ite; ++iti) {
                if( iti == ito ) continue;
                if( iti->at(0) <= ito->at(0) && ito->at(1) <= iti->at(1) ) {
                    ++r;
                    break; // no double counting
                }
            }
        }

        return n - r;
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
    vector<vector<int>> intervals;
    int r;

    // Example 1
    intervals = {{1,4},{3,6},{2,8}};
    cout << "{{1,4},{3,6},{2,8}}}" << endl;
    r = s.removeCoveredIntervals(intervals);
    cout << "result " << r << endl;
    assert(r == 2);

    // Example 2
    intervals = {{1,4},{2,3}};
    cout << "{{1,4},{2,3}}" << endl;
    r = s.removeCoveredIntervals(intervals);
    cout << "result " << r << endl;
    assert(r == 1);

    // Example 3
    intervals = {{0,10},{5,12}};
    cout << "{{0,10},{5,12}}" << endl;
    r = s.removeCoveredIntervals(intervals);
    cout << "result " << r << endl;
    assert(r == 2);

    // Example 4
    intervals = {{3,10},{4,10},{5,11}};
    cout << "{{3,10},{4,10},{5,11}}" << endl;
    r = s.removeCoveredIntervals(intervals);
    cout << "result " << r << endl;
    assert(r == 2);

    // Example 5
    intervals = {{1,2},{1,4},{3,4}};
    cout << "{{1,2},{1,4},{3,4}}" << endl;
    r = s.removeCoveredIntervals(intervals);
    cout << "result " << r << endl;
    assert(r == 1);



    // generate 1000 intervals with elements betweem 0 and 10e5
    intervals = {};
    srand(time(nullptr)); // use current time as seed for random generator
    for(int i = 0; i < 1000; ++i) {
        int rdm1 = rand() % 100001; // random in the range 0 and 10e5
        int rdm2 = rand() % 100001;
        while( rdm2 <= rdm1 ) rdm2 = rand() % 100001;
        intervals.push_back({rdm1,rdm2});
    }

    string str;
    int i = 1;
    for(auto interval : intervals) {
        cout << i << " " << interval[0] << " " << interval[1] << endl;
        if( i == 1 ) {
            str = "[[" + to_string(interval[0]) + "," + to_string(interval[1]) + "]";
        } else if ( i == 1000 ) {
            str += ",[" + to_string(interval[0]) + "," + to_string(interval[1]) + "]]";
        } else {
            str += ",[" + to_string(interval[0]) + "," + to_string(interval[1]) + "]";
        }
        ++i;
    }
    cout << endl;

    cout << "random 1000 intervals" << endl;
    start = chrono::system_clock::now();
    r = s.removeCoveredIntervals(intervals);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result " << r << endl;

    cout << str << endl;


    return 0;
}
