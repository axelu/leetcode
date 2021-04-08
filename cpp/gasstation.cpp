
// day 23 September 2020 challenge
// Gas Station
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3470/
// https://leetcode.com/problems/gas-station/


#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // gas and cost will have same size
        // one unique solution guaranteed, hence only one pass needed

        int fuelLevel = 0;
        auto start = gas.begin();
        int totalConsumption = 0; // to get around the circuit
        int totalCapacity = 0;

        auto itc = cost.begin();
        auto itg = start;
        for(; itg != gas.end(); ++itg) {
            cout << "idx " << distance(gas.begin(),itg) << endl;

            // fill
            fuelLevel += *itg;
            // drive
            fuelLevel -= *itc;

            cout << "fuelLevel " << fuelLevel << endl;

            if( fuelLevel < 0 ) {
                // advance start
                start = itg + 1;
                fuelLevel = 0;
            }

            totalConsumption += *itc;
            totalCapacity += *itg;

            ++itc;
        }

        if( totalConsumption > totalCapacity ) return -1;
        return distance(gas.begin(),start);
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

    vector<int> gas;
    vector<int> cost;

    gas = {1,2,3,4,5};
    cost = {3,4,5,1,2};
    // cout << s.canCompleteCircuit(gas,cost) << endl;
    assert(s.canCompleteCircuit(gas,cost) == 3);

    gas = {2,3,4};
    cost = {3,4,3};
    // cout << s.canCompleteCircuit(gas,cost) << endl;
    assert(s.canCompleteCircuit(gas,cost) == -1);

    gas = {5,1,2,3,4};
    cost = {4,4,1,5,1};
    // cout << s.canCompleteCircuit(gas,cost) << endl;
    assert(s.canCompleteCircuit(gas,cost) == 4);


    return 0;
}
