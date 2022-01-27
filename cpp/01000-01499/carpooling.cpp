
// day 21 September 2020 challenge
// 1094. Car Pooling
// https://leetcode.com/problems/car-pooling/


#include <iostream>
#include <cassert>

#include <vector>
#include <utility>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {

        // v will hold the number of riders at the begin
        // and end of each kilometer
        vector<vector<int>> v(1001, vector<int> (2, 0));

        for(auto trip : trips) {
            // pickup
            v[trip[1]][1] += trip[0];
            if( v[trip[1]][1] > capacity ) return false;

            // journey
            for(int i = trip[1] + 1; i < trip[2]; ++i) {
                v[i][0] += trip[0];
                if( v[i][0] > capacity ) return false;
                v[i][1] += trip[0];
                if( v[i][0] > capacity ) return false;
            }

            // drop off
            v[trip[2]][0] += trip[0];
            if( v[trip[2]][0] > capacity ) return false;
        }

        return true;
    }
};

int main() {

    Solution s;
    vector<vector<int>> trips;
    int capacity;

    trips = {{2,1,5},{3,3,7}};
    capacity = 4;
    assert(s.carPooling(trips,capacity) == false);

    trips = {{2,1,5},{3,5,7}};
    capacity = 4;
    assert(s.carPooling(trips,capacity) == true);

    trips = {{2,1,5},{3,3,7}};
    capacity = 5;
    assert(s.carPooling(trips,capacity) == true);

    trips = {{2,1,5},{3,5,7}};
    capacity = 3;
    assert(s.carPooling(trips,capacity) == true);

    trips = {{3,2,7},{3,7,9},{8,3,9}};
    capacity = 11;
    assert(s.carPooling(trips,capacity) == true);

    return 0;
}
