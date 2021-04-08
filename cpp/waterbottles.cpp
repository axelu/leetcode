
// Water Bottles
// https://leetcode.com/problems/water-bottles/


class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        if( numBottles < numExchange ) return numBottles;

        int r = 0;
        int e = 0; // number empty bottles

        while( numBottles + e >= numExchange ){
            // cout << "before numBottles   " << numBottles << endl;
            // cout << "before emptyBottles " << e << endl;
            r += numBottles;
            numBottles += e;
            e = numBottles % numExchange;
            numBottles = (numBottles / numExchange);
            // cout << "after numBottles    " << numBottles << endl;
            // cout << "afer emptyBottles   " << e << endl;
        }

        return r += numBottles;
    }
};
