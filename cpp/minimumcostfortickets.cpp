#include <iostream>
#include <cassert>

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// day 25 August 2020 challenge
// Minimum Cost For Tickets
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/552/week-4-august-22nd-august-28th/3436/

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        pDays = &days;
        pCosts = &costs;

        return mincostTickets(1); // start at the 1st possible travel day
    }
private:
    vector<int> *pDays;
    vector<int> *pCosts;
    unordered_map<int,int> minCostFromDay; // store calculated min cost for day X

    int mincostTickets(int d) {
        if ( d > 365 ) return 0; // year defined with 365 days

        // if we already had calculated it, return it
        auto it = minCostFromDay.find(d);
        if ( it != minCostFromDay.end() ) return it->second;

        int mincost;
        auto td = find(begin(*pDays), end(*pDays), d);
        if ( td != end(*pDays) ) {
            // d is a travel day          
            mincost = min({pCosts->at(0) + mincostTickets(d + 1),
                           pCosts->at(1) + mincostTickets(d + 7),
                           pCosts->at(2) + mincostTickets(d + 30)});
        } else {
            // d is not a travel day, move on to the next day
            mincost = mincostTickets(d + 1);
        }

        minCostFromDay.insert({d, mincost}); // store for future retrieval
        
        return mincost;
    }
};

int main() {
    Solution s;

    vector<int> days;
    vector<int> cost;

    days = {1,4,6,7,8,20};
    cost = {2,7,15};
    assert(s.mincostTickets(days, cost) == 11);

    return 0;
}
