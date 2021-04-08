
// Minimum Number of Arrows to Burst Balloons
// day 10 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3490/
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/


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
#include <climits>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

// https://stackoverflow.com/questions/32773855/random-number-between-int-max-int-min
int gen_random_int() {
    const int BITS_PER_RAND = (int)(log2(RAND_MAX/2 + 1) + 1.0);
    int ret = 0;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
        ret <<= BITS_PER_RAND;
        ret |= rand();
    }
    return ret;
}


class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        auto n = points.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;

        sort(begin(points),end(points),[](vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        });

        int r = 1;
        int as = points[0][0]; // range of arrow  start
        int ae = points[0][1]; // range of arraow end
        for(int i = 1; i < n; ++i) {
            if( points[i][0] > ae ) {
                ++r; // next arrow
                as = points[i][0];
                ae = points[i][1];
                continue;
            } else if( points[i][0] == ae ) {
                as = ae;
                continue;
            }
            as = points[i][0];
            ae = min(ae,points[i][1]);
        }

        return r;
    }
};


int main() {

    Solution s;
    vector<vector<int>> points;
    string example;
    int r;

    example = "Example 1";
    cout << example << endl;
    points = {{10,16},{2,8},{1,6},{7,12}};
    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;
    assert(r == 2);

    example = "Example 2";
    cout << example << endl;
    points = {{1,2},{3,4},{5,6},{7,8}};
    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;
    assert(r == 4);

    example = "Example 3";
    cout << example << endl;
    points = {{1,2},{2,3},{3,4},{4,5}};
    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;
    assert(r == 2);

    example = "Example 4";
    cout << example << endl;
    points = {{1,2}};
    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;
    assert(r == 1);

    example = "Example 5";
    cout << example << endl;
    points = {{2,3},{2,3}};
    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;
    assert(r == 1);

    // generate 10e4 random points with x and y between -2e31 and 2e31 - 1 (INT_MIN and INT_MAX)
    cout << "random" << endl;
    srand(time(nullptr)); // use current time as seed for random generator
    int rdm1, rdm2;
    points = {};
    int n = 1000;
    for(int i = 0; i < n; ++i) {
        int rdm1 = gen_random_int();// random in the range INT_MIN and INT_MAX
                                    // -2147483648 to 2147483647
        int rdm2 = gen_random_int();
        while( rdm2 <= rdm1 ) rdm2 = gen_random_int();
        points.push_back({rdm1,rdm2});
    }

    string str;
    int i = 0;
    for(auto vi : points) {
        if( i == 0 ) {
            str = "[[" + to_string(vi[0]) + "," + to_string(vi[1]) + "]";
        } else if ( i == n - 1) {
            str += ",[" + to_string(vi[0]) + "," + to_string(vi[1]) + "]]";
        } else {
            str += ",[" + to_string(vi[0]) + "," + to_string(vi[1]) + "]";
        }
        ++i;
        // cout << vi[0] << " " << vi[1] << endl;
    }
    cout << str << endl;

    r = s.findMinArrowShots(points);
    cout << "result " << r << endl;

    return 0;
}
